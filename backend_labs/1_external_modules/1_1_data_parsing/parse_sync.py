import argparse
import json
import os

import httpx
from bs4 import BeautifulSoup



_root = os.path.dirname(os.path.realpath(__file__))
_page_cache_path = f"{ _root }/cached_pages/"
_parse_page_link = 'https://www.lookup.pk/dynamic/search.aspx'
_default_params = dict(
    searchtype="kl",
    k="gym",
    l="lahore",
    page=1
)



def read_json() -> dict:
    """Just handle file-reading routine and JSON parsing
    """
    try:
        with open('./parsed_data.json', ) as f_:
            return json.loads(f_.read())
    except OSError:
        print("Can't read file")
        return


def get_cli_arguments() -> argparse.Namespace:
    """Read specified command line arguments and return parsed args
    """
    ap = argparse.ArgumentParser(description='Parse search page lookup.pk')
    ap.add_argument('-m', '--max-pages-count', type=int, default=20)
    ap.add_argument('-r', '--continue-parsing', type=bool, default=False)

    return ap.parse_args()


def get_page_cache(page_num: int) -> bytes:
    page_filepath = f"{ _page_cache_path }page_{ page_num }"
    try:
        with open(page_filepath) as f_:
            return f_.read()
    except OSError as e:
        print('Info: cached page not found: ', e)

def cache_page_contents(contents: bytes, page_num: int):
    page_filepath = f"{ _page_cache_path }page_{ page_num }"
    try:
        with open(page_filepath, 'wb') as f_:
            f_.write(contents)
    except OSError as e:
        print('Failed to save page contents to the cache: ', e)


def get_page_contents(page_num: int = 1):
    """Retrieve web page contents and cache it

    Makes http GET request for page and stores its content into a cache
    or reads contents from cache and just returns
    """

    _default_params['page'] = page_num
    cached_contents = get_page_cache(page_num)
    
    if cached_contents:
        return cached_contents
    contents = httpx.get(_parse_page_link, params=_default_params).content
    if contents:
        cache_page_contents(contents, page_num)
    return contents


def make_preemptive_env_checks():
    """Prepare needed environment.

    This is not to be confused with shell Environment.
    This function takes some preparation steps to make sure
    the script has all it needs to work
    """
    if not os.path.exists(_page_cache_path):
        os.makedirs(_page_cache_path)


def start_parsing(max_pages: int, start_from_savepoint: bool):
    data = None

    make_preemptive_env_checks()

    if start_from_savepoint:
        data = read_json()
    
    raw_page = get_page_contents()

    cook_soup()
    


if __name__ == '__main__':
    args = get_cli_arguments()
    start_parsing(args.max_pages_count, args.continue_parsing)