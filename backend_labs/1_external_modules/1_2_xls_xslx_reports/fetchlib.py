import httpx

import cachelib as caching



_parse_page_link = 'https://www.lookup.pk/dynamic/search.aspx'
_default_params = dict(
    searchtype="kl",
    k="gym",
    l="lahore",
    page=1
)



async def get_page_contents(page_num: int, query_str: str, query_hash: str):
    """Retrieve web page contents and cache it

    Makes http GET request for page and stores its content into a cache
    or reads contents from cache and just returns
    ...

    Arguments:
    ----------
        page_num: int
            this is used for pagination to receive exactly needed page
        query_str: str
            query string to search for on remote
        query_hash: str
            query hash to avoid regenerating it eachtime
            this serves as unique search session identifier
            to store files under different paths for different searches
    Returns:
    --------
        - contents
            bytes received from cache or from request result
            containing HTML-page response
    """

    _default_params['page'] = page_num
    _default_params['k'] = query_str
    cached_contents = caching.get_page_cache(page_num, query_hash)

    # Either make request and receive fresh page bytes and cache it
    # or get it from cache
    # =
    if cached_contents:
        return cached_contents
    
    print("Trying to retrieve page from remote host")
    try:
        async with httpx.AsyncClient() as ar:
            resp = await ar.get(_parse_page_link,
                                params=_default_params, timeout=5)
            
            if resp.status_code == 200:
                caching.cache_page_contents(resp.content, page_num, query_hash)
                await caching.increment_fetched_pagescount(query_hash)
                return resp.content
    except httpx.TimeoutException as e:
        print(f"Request timeout for page {page_num}: ")
        return