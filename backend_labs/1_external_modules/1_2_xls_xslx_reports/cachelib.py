import os
import csv
import json
from enum import Enum

import openpyxl

from redislib import AIORedisConnectionManager



_root = os.path.dirname(os.path.realpath(__file__))
_page_cache_path = f"{ _root }/.cached_pages/"
_parse_results_dir = f"{ _root }/parse_results/"
__redis_session = AIORedisConnectionManager(database=1)



class ResultsFormat(str,Enum):
    json: str = 'json'
    csv: str = 'csv'
    xlsx: str = 'xlsx'


class CachingSettings:
    __slots__ = [
        'filetype'
    ]

    def __init__(self):
        self.filetype = ResultsFormat.json

    def set_filetype(self, type_: str):
        if not isinstance(type_, str):
            type_ = 'json'
        self.filetype = getattr(ResultsFormat, type_).value




settings = CachingSettings()



def compose_path(common_path: str, results_path: str, page_num: int = None):
    composed_path = f"{ common_path }{ results_path }/"

    if not os.path.exists(composed_path.strip()):
        os.makedirs(composed_path)
    if page_num:
        composed_path = f"{ composed_path }page_{ page_num }"

    return composed_path


def cache_page_contents(contents: bytes, page_num: int, result_id: str):
    """Store received HTML contents to local file-cache.
    ...

    Arguments:
    ----------
        - contents: bytes
            raw HTML data to cache
        - page_num: int
            is a formality to make cache look more organized and spare
            to store any particular page under its specific ID
    """
    page_filepath = compose_path(_page_cache_path, result_id, page_num)

    try:
        with open(page_filepath, 'wb') as f_:
            f_.write(contents)
    except OSError as e:
        print('Failed to save page contents to the cache: ')


def get_page_cache(page_num: int, resutl_id: str) -> bytes:
    """Retrieve cached HTML contents from local file-cache.
    ...

    Arguments:
    ----------
        - page_num: int
            is a formality to make cache look more organized and spare
            to store any particular page under its specific ID

    Returns:
    --------
        - contents: bytes
            return the requested cached HTML page in bytes
            or None
    """
    page_filepath = compose_path(_page_cache_path, resutl_id, page_num)
    try:
        with open(page_filepath) as f_:
            return f_.read()
    except OSError as e:
        print('Info: cached page not found: ')


def get_stored_last_pagenum(result_id: str):
    filepath = compose_path(_page_cache_path, result_id)
    filepath = f"{ filepath }/last_pagenum.txt"
    try:
        with open(filepath) as f_:
            return int( f_.read() )
    except OSError:
        print("Failed to retrieve last parsed page number from a cache file")
        return 0

def store_last_pagenum(page_num: int, result_id: str):
    filepath = compose_path(_page_cache_path, result_id)
    filepath = f"{ filepath }/last_pagenum.txt"
    try:
        with open(filepath, 'w') as f_:
            f_.write( str(page_num) )
    except OSError as e:
        print("Failed to store last parsed page number to a cache file")
        print("Error: ", e)


async def cache_pagenum(pagenum, result_id: str):
    rediskey = f"data_parsing_lab:{ result_id }:last_pagenum"
    async with __redis_session() as rdb:
        await rdb.set(rediskey, pagenum)
        await rdb.expire(rediskey, 3600)


async def get_cached_pagenum(result_id: str):
    rediskey = f"data_parsing_lab:{ result_id }:last_pagenum"
    async with __redis_session() as rdb:
        result = await rdb.get(rediskey)
        if result:
            return int(result.decode())


async def clear_cached_pagenum(result_id: str):
    rediskey = f"data_parsing_lab:{ result_id }:last_pagenum"
    async with __redis_session() as rdb:
        await rdb.delete(rediskey)


async def count_results(count: int, result_id: str):
    rediskey = f"data_parsing_lab:{ result_id }:resultcount"
    async with __redis_session() as rdb:
        await rdb.incrby(rediskey, count)


async def get_results_count(result_id: str):
    rediskey = f"data_parsing_lab:{ result_id }:resultcount"
    async with __redis_session() as rdb:
        try:
            result = await rdb.get(rediskey)
            return int( result.decode() )
        except:
            ...

async def clear_results_count(result_id: str):
    rediskey = f"data_parsing_lab:{ result_id }:resultcount"
    async with __redis_session() as rdb:
        try:
            await rdb.delete(rediskey)
        except Exception as e:
            print("Error deleting key: ", e)


async def increment_fetched_pagescount(result_id: str):
    rediskey = f"data_parsing_lab:{ result_id }:downloaded"
    async with __redis_session() as rdb:
        result = await rdb.incr(rediskey, amount=1)


async def get_fetched_pagescount(result_id: str):
    rediskey = f"data_parsing_lab:{ result_id }:downloaded"
    async with __redis_session() as rdb:
        result = await rdb.get(rediskey)
        print(result)
        if result:
            return result.decode()



def check_stored_result(page_num: str, result_id: str):
    filepath = compose_path(_parse_results_dir, result_id, page_num)
    filepath = f"{ filepath }.{ settings.filetype }"
    
    return os.path.exists(filepath)


def store_parse_results(parse_results, page_num: str, result_id: str):
    """Store all parsed data to the specific directory.
    This specific directory is composed from:
        - common results directory where all the results are stored
        - additional directory which corresponds to specific search query
          so results for different search queries are not overlapped
    And there goes filename which is: page_<number>.json.
    ...

    Parameters:
    -----------
        - parse_results: list
            this is parsed page fields which are to be stored for page
        - result_id: str
            this id will be used as directory name
            for specific search query results
        - page_num: int/str
            page id will be used as file name for data for that parsed page
    """
    filepath = compose_path(_parse_results_dir, result_id, page_num)
    filepath = f"{ filepath }.{ settings.filetype }"
    

    # if ftype == ResultsFormat.xlsx:
    #     store_xlsx(parse_results, filepath)
    #     return
        
    try:
        with open(filepath, 'w') as f_:
            if settings.filetype == ResultsFormat.json:
                f_.write( json.dumps(parse_results, indent=4) )
                return
            if settings.filetype == ResultsFormat.csv:
                fields = parse_results[0]
                writer = csv.DictWriter(f_, fieldnames=fields)
                writer.writeheader()
                writer.writerows(parse_results)
                return
            if settings.filetype == ResultsFormat.xlsx:
                wb = openpyxl.Workbook()
                ws = wb.active

                ws.title = "Page " + str(page_num)

                # Insert titles row
                ws.append([ *parse_results[0] ])


                alignm = openpyxl.styles.alignment.Alignment(
                        horizontal="center",
                        vertical="center",
                        wrapText=False)
                ws.row_dimensions[1].alignment = alignm
                
                for row in parse_results:
                    row['phone_numbers'] = "; ".join(row['phone_numbers'])
                    ws.append(list(row.values()))

                alignm = openpyxl.styles.alignment.Alignment(
                        horizontal="center",
                        vertical="center",
                        wrapText=False)
                wb.save(filepath)
    except OSError as e:
        print("Unable to write parsed page data to file: ", filepath)
        print("Error: ", e)


def save_execution_meta(metainfo: dict, result_id: str):
    """Save information about program execution to a file
    Info will be stored inside of XLSX file


    Parameters:
    -----------
        metainfo: dict
            dctionary contains meta information
        reuslt_id: str
            is specific to current search query
            to store info to the right directory
    
    """
    filepath = compose_path(_parse_results_dir, result_id)

    wb = openpyxl.Workbook()
    ws = wb.active

    ws.title = "Parsing metainfo"

    # Insert titles row
    ws.append([*metainfo])
    ws.append(list(metainfo.values()))

    alignm = openpyxl.styles.alignment.Alignment(
            horizontal="center",
            vertical="center",
            wrapText=False)
    ws.row_dimensions[1].alignment = alignm
    ws.row_dimensions[2].alignment = alignm

    wb.save(f"{filepath}/metainfo.xlsx")
