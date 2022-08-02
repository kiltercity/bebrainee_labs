# Python Backend Tasks
Has: 10 tasks totally

---
## Contents
* [External Modules](#1-external-modules):
    * [Data Parsing](#11-data-parsing)
    * CSV/XLSX Reports
    * Queues
    * Image processing
* Simple Socieal Network
    * Databse structure and Migrations
    * Creating posts; user profile and its friends
    * Administrator interface
* Optimization
    * Quey scheduler and Indexes
    * Caching and Full-Text search
    * Event-Driven architecture



---
### 1. External Modules
#### 1.1. Data Parsing
  * Location: `1_external_modules/1_1_data_parsing`
  * Files:
    - `parse.py` - the script for performing parsing *stuff*
    - `parsed_page_<num>.json` - specific parsed with BS4 page
        where <num> is the numper of page in pagination loop
    - `.cached_pages/` - directory containing *cached* HTML-pages from HTTP response to avoid issuing excessive amount of requests
    - `parse_results/` - is produced by script as well as `.cached_pages
      contains a list of files with parsed data.
      Files are distibuted amond directories that has md5 hash as its names.
      These directories correspond to search queries hashes (see below).
    
  * Task:
    - a) Expose command interface for data parsing from a specific resourse and saving data of a fixed format as JSON
    - b) If the resourse (web) supports pagination facilities, then implement
        the ability to stop at some point and then continue when script is restarted 

  * Implementation brief:
    - Script implements plethora of functions which break the whole application down to more readable and comprehensive parts (or logical units - if you wish)
    - The main functionality is next:
      - Script can fetch search results for specific query from determined web-resource: lookup.pk
      - When a specific page is fetched it gets cached. Each fetched page is going to be cached, to avoid redundant requests.
      - Page cache is stored at : `.cached_pages` and grouped by search queries (in particular: search query hashes).
      - Then a parsing process is started using BeautifulSoup4.
      - Parsed data is stored in plain JSON under the `parse_results/` directory,
        grouped by directories for specific search query with search query md5 hash as directory name
      - Script can restart from last remembered successfully parsed page.
      - Script allows user to specify search query
      - Script allows user to specify amount of parsed pages for one parsing session
  * Usage:
    - Just call the script with/without params and enjoy the results:
    ```
    python parse.py -m 20 -r -s search_query
    ```
  * Available options:
    - `-m <num>` or `--max-pages-count <num>` - maximum pages to parse
    - `-r` or `--continue-parsing` - continue from the page where you left off
    - `-s` or `--search-query`  - custom user search query
    
   * Warnings:
    - Script does use NO proxy, so the frequent sequence of requests can be blocked by resource
    - Script makes a little delay, but if it was too big delay it would annihilate the purpose of using asyncio facilities
    - It can be solved manually by going to https://www.lookup.pk/dynamic/search.aspx?searchtype=kl&k=search&l=lahore
      , solving the easy captcha and then restarting the script

    

+++++++++++++++++
#### 1.2. CSV/XLSX Reports
  * Location: 
  * Files:
  * Task:
  * Implementation brief:
  * Usage:
  * Available options:


---
### 2. Simple Social Network


---
### 3. Optimization
