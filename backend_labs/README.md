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
  * Task:
    - a) Expose command interface for data parsing from a specific resourse and saving data of a fixed format as JSON
    - b) If the resourse (web) supports pagination facilities, then implement
        the ability to stop at some point and then continue when script is restarted 

  * Implementation brief:
    - Script implements plethora of functions which break the whole application down to more readable and comprehensive parts (or logical units - if you wish)

  * Usage:
    - Just call the script with/without params and enjoy the results:
    ```
    python parse.py -m 20 -r
    ```
  * Available options:
    - `-m <num>` or `--max-pages-count <num>` - maximum pages to parse
    - `-r` or `--continue-parsing` - continue from the page where you left off

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
