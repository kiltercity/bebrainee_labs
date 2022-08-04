#!/usr/bin/env python3
import asyncio
import time
from datetime import datetime
import argparse
import queue
import hashlib

import fetchlib
import parselib
import cachelib as caching




_default_search_query = "gym"


def get_cli_arguments() -> argparse.Namespace:
    """Read specified command line arguments and return parsed args.
    ...

    Returns:
    --------
        parsed arguments Namespace created by argparse:
            - .max_pages_count
                is maximum pages specified when script is invoked
                or by default is 20
            - .continue_parsing
                whether to continue parsing from the page
                where script ended last time
                by default: False
            - .search_query
                specific search query to ask remote website for
    """
    ap = argparse.ArgumentParser(description='Parse search page lookup.pk')
    ap.add_argument('-m', '--max-pages-count', type=int, default=20)
    ap.add_argument('-r', '--continue-parsing', action='store_true')
    ap.add_argument('-s',
                    '--search-query',
                    type=str,
                    default=_default_search_query)
    ap.add_argument('-f', '--result-filetype', type=str, choices=[*caching.ResultsFormat])
    return ap.parse_args()


async def parse_worker(tqueue):
    """Manages parsing flow.
    This is basically an async task.
    Fetches contents. Parses results and stores them.
    ...

    Parameters:
    -----------
        - tqueue: object
            this is an async queue object, which holds:
                * currently handled page number
                * search query hash (to identify different parsing results)
                * event tuple: previous task event and current task event
                    this is needed 
                    to manage some consistency and orering among tasks
    Returns:
    --------
        - Page number or None
    """
    print("+" * 80)


    # Unpacking data from queue
    #
    # the queue preserves the order of page parsing
    page_num, squery, finish_events = tqueue.get()
    query_str, query_hash = squery
    prev_task_ev, curr_task_ev = finish_events
    

    # If some file exists under the currently parsed data path
    # then we consider this task was already done
    # 
    if caching.check_stored_result(page_num, query_hash):
        print(f"Nothing to do here. Already parsed: Page: {page_num}")
        curr_task_ev.set()
        return

    print(f"Working on: Page { page_num }")

    # If we cannot retrieve HTML page contents to parse from - quit
    #
    contents = await fetchlib.get_page_contents(page_num, query_str, query_hash)
    if not contents:
        print("No contents for this page: ", page_num)
        curr_task_ev.set()
        return

    # Cook soup (parse html contents and write them to a file)
    #
    parse_results, results_count = parselib.bs4_parse_page(contents)
    if parse_results:
        await caching.count_results(results_count, query_hash)
        caching.store_parse_results(parse_results, page_num, query_hash)

    # Wait until previous task is finished
    if prev_task_ev:
        await prev_task_ev.wait()

    # store last page number to cache
    # see now? this respects the needed order
    # and still doesn't prevent asynchronous above
    #
    await caching.cache_pagenum(page_num, query_hash)
    curr_task_ev.set()
    print("Finished : page ", page_num)
    return page_num

    
async def cook_soup(max_pages: int,
                    start_from_savepoint: bool,
                    search_query_str: str,
                    result_filetype: str):
    """Manage all the steps needed to read, parse and store the data.
    ...

    Arguments:
    ----------
        - max_pages: int
            allowed maximum pages to parse at a time
        - start_from_savepoint: bool
            continue from where the script finished last time
            (from the last parsed page number)
    
    Returns:
    --------
        None
    """
    exec_start = time.time()
    timeformat = "%b %d %Y %H:%M:%S.%f"
    start_time = datetime.now().strftime(timeformat)

    # search_query_id
    search_query_hash = hashlib.md5(search_query_str.encode()).hexdigest()
        
    start_from = 0
    pages_range = range(1, max_pages + 1)
    tasks = []
    tqueue = queue.Queue(max_pages)

    # Clear previous page results count
    await caching.clear_results_count(search_query_hash)

    # Set parsed data results filetype
    caching.settings.set_filetype(result_filetype)

    # Restart where we ended last time
    if start_from_savepoint:
        start_from = caching.get_stored_last_pagenum(search_query_hash)

    # Push page numbers to queue
    # * Also pass search query hash,
    #   so the results saved for particular search query
    # * Pass Event synchronization primitive
    #   to achieve consistent caching of last page number
    #
    evts = (None, asyncio.Event())
    prev_task_ev = None
    squery = (search_query_str, search_query_hash)
    for offset in pages_range:
        tqueue.put((start_from + offset, squery, evts))

        evts = (prev_task_ev, asyncio.Event())
        _, prev_task_ev = evts
    
    # start parsing tasks concurrently (passing the queue to preserve order)
    for c in pages_range:
        # we need to create a strong referrence to the task object
        # as the << create_task >> method creates only WEAK reference
        #
        task = asyncio.create_task(parse_worker(tqueue))
        tasks.append(task)

    # Wait until all the task are completed
    #
    await asyncio.gather(*tasks)

    # Save last parsed page number
    #
    last_pagenum = await caching.get_cached_pagenum(search_query_hash)
    caching.store_last_pagenum(last_pagenum, search_query_hash)
    
    # Retrieve and save program results
    #
    exec_end = time.time()
    exec_time = round(exec_end - exec_start, 5)
    end_time = datetime.now().strftime(timeformat)
    handled_pages =  await caching.get_fetched_pagescount(search_query_hash)
    
    time_meta = {
        "Start time": start_time,
        "Execution time": exec_time,
        "End time": end_time,
        "Results count": await caching.get_results_count(search_query_hash),
        "Fetched pages": handled_pages }
    caching.save_execution_meta(time_meta, search_query_hash)


if __name__ == '__main__':
    args = get_cli_arguments()
    print(args.result_filetype)
    asyncio.run(cook_soup(
        args.max_pages_count,
        args.continue_parsing,
        args.search_query,
        args.result_filetype
    ))