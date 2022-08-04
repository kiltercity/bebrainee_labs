import json
from bs4 import BeautifulSoup



def bs4_parse_page(html_contents):
    soup = BeautifulSoup(html_contents, 'html.parser')
    results = soup.find_all('div', 'CompanyInfo')
    parsed_data = []
    soup = None # free for GC
    results_count = 0
    
    for block in results:
        results_count += 1
        header = block.find('a', 'DetailPageLink').find('h2').string
        rating = next( (block.find('div', 'CompanyRating')
                        .find('div', 'inline').stripped_strings) )
        address = "".join(block.find('address').stripped_strings)
        phone_numbers = block.find('li', 'viewNumber').find('ul', 'submenu')

        # Extract rating if there is one
        #
        rating = rating[:-2] # remove ">>" at the end
        if rating[0] == '|':
            rating = rating[2:8]

        # Get numbers list for this company
        #
        parsed_numbers = []
        for number in phone_numbers:
            num = number.find('a')
            if num != -1:
                parsed_numbers.append(num.string)

        parsed_data.append({
                "header": header,
                "rating": rating,
                "address": address,
                "phone_numbers": parsed_numbers })
    return ( parsed_data, results_count )