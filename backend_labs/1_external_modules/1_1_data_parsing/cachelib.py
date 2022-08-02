import os
from redislib import AIORedisConnectionManager



_root = os.path.dirname(os.path.realpath(__file__))
_page_cache_path = f"{ _root }/.cached_pages/"
_parse_results_dir = f"{ _root }/parse_results/"
__redis_session = AIORedisConnectionManager(database=1)




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


def check_stored_result(page_num: str, result_id: str):
    filepath = compose_path(_parse_results_dir, result_id, page_num)
    filepath = f"{ filepath }.json"
    
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
    filepath = f"{ filepath }.json"

    try:
        with open(filepath, 'w') as f_:
            f_.write(parse_results)
    except OSError as e:
        print("Unable to write parsed page data to file: ", filepath)
        print("Error: ", e)
