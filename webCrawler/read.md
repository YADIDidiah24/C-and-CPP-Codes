Abstract:
This report presents the code and implementation of a multi-threaded web crawler for traversing and analysing web content. The crawler is developed in C++ using the libcurl library, also threads are used to show a multithreaded and concurrent approach to analyse websites. The primary goal of the code is to rank the websites based on the number of hyperlinks discovered in each website.

The main website is crawled using the depth-first search (DFS) method, with a unique bot id assigned to each thread. The program initiates threads for a set of websites. Each thread downloads the HTML content of a webpage, extracts, cleans, and validates hyperlinks, to ensure only legitimate URLs are considered. The ranking mechanism accumulates the number of hyperlinks associated with each main website, providing a measure of its connectivity.
The ranking algorithm counts the number of connections (hyperlinks)  connected to every website, to assess how connected the website is.

the crawler uses multi-threading, allowing for concurrent processing of different websites. A mutex lock is present to ensure synchronized access to shared data, like execution count, website ranking, and visited URLs. The crawler has a depth-limiting mechanism, restricting only to a fixed number of levels from the primary webpage.

The final output gives the ranking of main websites based on the number of hyperlinks discovered during crawling. The report discusses the implementation details, challenges faced, and future improvements for scalability and performance optimization. Overall, the multi-threaded web crawler offers an important set of features for exploring and analysing website connectivity using an effective concurrent technique.
The process looks like this

graph TD.
    A[Start] --> B[Download webpage]
    B --> C[Extract links]
    C --> |Valid links?| D[Clean up links]
    D --> |More links to crawl?| E[DFS crawler]
    E --> |More threads to join?| F[Join threads]
    F --> G[Calculate PageRank]
    G --> H[Sort rankings]
    H --> I[Print rankings]
    I --> J[End]

The code:
The code consists of various functions to set the environment the functions are as follows,

1.	void get_page(const char* url, const char* file_name)
This function  retrieves the html from the link and stores it in a text file.
1.	This initializes a CURL handle (easyhandle) to be used for making HTTP requests.
2.	Sets the URL to be fetched using the initialized CURL handle.
3.	Opens a file for writing. If the file already exists, its content is cleared.
4.	Sets the option to write the received data into the specified file.
5.	Executes the HTTP request and writes the received data into the opened file.
6.	Cleans up the resources associated with the CURL handle.
7.	Closes the file.


2.	vector<string> extract_hyperlinks(string html_file_name )
•	The function takes a file name as input, opens the file (html_file_name) using an ifstream for reading (read), and reads the content character by character until the end of the file. The characters are appended to the html string.
•	After reading, the file is closed using read.close().
•	A regular expression (hl_regex) is defined to match the pattern <a href="(.*?)">. This regex is used to capture the content within the href attribute of HTML anchor tags (<a>), which typically represents hyperlinks. Icase means it is not case sensitive.
•	The sregex_token_iterator is used to tokenize the html string based on the regex pattern. The captured content (links) is stored in the links vector.
•	Return Links:
•	The vector containing the extracted links is returned.


3.	void cleanUp(vector<string>&all_links )

1.	final_links: This vector is used to store the cleaned and validated links.
2.	The function iterates through each link in the all_links vector.
3.	It removes spaces and double quotations from each link.
4.	It checks if the cleaned link matches a specific regex pattern, which is designed to validate URLs. The regex ensures that the link has a valid format for a URL.
5.	If the link is valid, it is added to the final_links vector.
6.	After processing all links, the original vector all_links is cleared, and its contents are replaced with the contents of the final_links vector.

4.	void dfs_crawler(const char* url, const char* file_path, int bot_id)

•	This is the main function in the program as this is the one that crawls the links and gets the data.
•	The function initiates the crawling process by calling the above functions for downloading the HTML content, extracting hyperlinks, and cleaning them up.
•	The cleaned links are then used to recursively call the dfs_crawler function for further exploration.
•	The program uses multi-threading to allow concurrent crawling of different websites, with each thread identified by a unique bot_id.
•	The crawler limits the exploration depth to 10 levels from the initial webpage.
•	The program maintains shared data structures like execution count, website ranking, and visited URLs, with thread synchronization using a mutex.

Code initialization:
The code was implemented in kali Linux.
┌──(yadidiah㉿kali)-[~]
└─$ cd web_crawler
   
                                                                    
┌──(yadidiah㉿kali)-[~/web_crawler]
└─$ nano webCrawler.cpp
    
                                                             
┌──(yadidiah㉿kali)-[~/web_crawler]
└─$ g++ webCrawler.cpp -o webCrawler -lcurl -lpthread
     
                                                                         
┌──(yadidiah㉿kali)-[~/web_crawler]
└─$ ./webCrawler     

Running code snippets: For the primary websites as 
  vector<string> mainWebsites = {
    "https://www.tofugu.com/learn-japanese/",
    "https://github.com/",
    "https://codeforces.com/",
    "https://www.youtube.com/",
    "https://www.cud.ac.ae/",
    "https://leetcode.com/problemset/all/"
  };


 
 
Website Ranking:
1st Position: https://www.cud.ac.ae/  Number of Hyperlinks Found: 24
2st Position: https://codeforces.com/  Number of Hyperlinks Found: 16
3st Position: https://github.com/  Number of Hyperlinks Found: 10
4st Position: https://www.tofugu.com/learn-japanese/  Number of Hyperlinks Found: 4
5st Position: https://leetcode.com/problemset/all/  Number of Hyperlinks Found: 0
6st Position: https://www.youtube.com/  Number of Hyperlinks Found: 0

Total Number of Websites Crawled by All Threads: 260
                                                       

(Note: The position of the webpage is only based on the number of hyperlinks each website carries)

Recommendations for system improvement:
- We would like to add more algorithms for ranking websites  like a simplified PageRank Algorithm, HITS (Hyperlink-Induced Topic Search) Algorithm or the ALEXA Rank algorithm.

Conclusion: 
This project was successful in developing a multi-threaded web crawler, that explores websites, it was also successful in downloading content from multiple websites simultaneously. Although many things like indexes could be added and more algorithms could be used to make website ranking more better.
