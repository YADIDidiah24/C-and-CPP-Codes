#include <iostream>
#include <vector>
#include <unordered_map>
#include <curl/curl.h>
#include <stdio.h>
#include <regex>
#include <thread>
#include <mutex>
#include <chrono>
#include <atomic>
#include <fstream>
using namespace std;

mutex m;

unordered_map<int, int> executionCount;
unordered_map<string, int> websiteRanking;
unordered_map<string, vector<string>> websiteGraph;

atomic<int> totalWebsitesCrawled(0);

// download html in file
void get_page(const char* url, const char* file_name)
{
    CURL* easyhandle = curl_easy_init(); // initialize the curl Object

    curl_easy_setopt(easyhandle, CURLOPT_URL, url);
    FILE* file = fopen(file_name, "w"); // make object for file handling

    curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, file); // write to file
    curl_easy_perform(easyhandle);                        // structure the html code
    curl_easy_cleanup(easyhandle);                         // erase the html from curl_object/buffer
    fclose(file);
}

// extract links from file
vector<string> extract_hyperlinks(string html_file_name)
{
    string html; // here we will store the html from file
    ifstream read; // ifstream object for reading the file
    read.open(html_file_name);
    while (!read.eof()) // reading the file character by character
    {
        if (read.eof())
            break; // stop if file is ended
        char ch;
        read.get(ch);
        html.push_back(ch); // concatenate the character reading from file to string
    }
    read.close();
    static const regex hl_regex("<a href=\"(.*?)\">", regex_constants::icase); // icase means not case sensitive
    vector<string> links;                                                      // it will store all the links read from the file
    // below line will store all found links in vector
    copy(sregex_token_iterator(html.begin(), html.end(), hl_regex, 1), sregex_token_iterator(), back_inserter(links));
    return links;
}

// validate the links
void cleanUp(vector<string>& all_links)
{
    vector<string> final_links; // it will store all the valid links
    for (int i = 0; i < all_links.size(); i++) // cleaner
    {
        string one_link = all_links[i]; // pick one link
        string cleaned_link = "";       // it will store cleaned link
        for (int j = 0; j < one_link.length(); j++)
        {
            if (one_link[j] == ' ' || one_link[j] == 34)
                break; // stops if it will find empty space or double quotation
            cleaned_link.push_back(one_link[j]); // concatenating character by character to string
        }
        // after getting the useful part now validate the link, if the URL is good to go then add it to the final_vector
        if (regex_match(cleaned_link, regex("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)")))
        {
            final_links.push_back(cleaned_link);
        }
    }
    all_links.clear();      // clear the original vector
    all_links = final_links; // replace it with the final links vector
}

unordered_map<string, bool> visited; // used while dfs to identify if the URL is already visited or not + Insertion TC = O(1)

void dfs_crawler(const char* url, const char* file_path, int bot_id)
{
    string s = url;
    visited[s] = 1;

    vector<string> allLinksData;
    m.lock();
    cout << "Bot_id: " << bot_id << "\tLink: " << url << endl;
    get_page(url, file_path);
    allLinksData = extract_hyperlinks(file_path);
    cleanUp(allLinksData);
    websiteRanking[url] += allLinksData.size(); // Accumulate the ranking for the main website
    websiteGraph[url] = allLinksData;           // Store the graph structure
    m.unlock();

    if (++executionCount[bot_id] < 10)
    {
        for (const string& i : allLinksData)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            const char* c = i.c_str();
            if (visited[i] != 1)
                dfs_crawler(c, file_path, bot_id);
        }
    }

    // Increment the total number of websites crawled by this thread
    totalWebsitesCrawled++;
}

void calculate_pagerank()
{
    unordered_map<string, double> pageRankScores;
    double dampingFactor = 0.85;
    double convergenceThreshold = 0.0001;

    // Initialize pageRankScores
    for (const auto& entry : websiteRanking)
    {
        pageRankScores[entry.first] = 1.0 / websiteRanking.size();
    }

    size_t numIterations = 100;
    for (size_t iter = 0; iter < numIterations; ++iter)
    {
        unordered_map<string, double> newPageRankScores;

        for (const auto& entry : websiteRanking)
        {
            const string& page = entry.first;
            const vector<string>& incomingLinks = websiteGraph[page];

            double contribution = 0.0;
            for (const string& incomingLink : incomingLinks)
            {
                size_t numOutgoingLinks = websiteGraph[incomingLink].size();
                contribution += pageRankScores[incomingLink] / static_cast<double>(numOutgoingLinks);
            }

            newPageRankScores[page] = (1.0 - dampingFactor) / websiteRanking.size() + dampingFactor * contribution;
        }

        // Check for convergence
        double convergence = 0.0;
        for (const auto& entry : websiteRanking)
        {
            const string& page = entry.first;
            convergence += abs(pageRankScores[page] - newPageRankScores[page]);
        }

        if (convergence < convergenceThreshold)
        {
            cout << "PageRank Converged after " << iter + 1 << " iterations." << endl;
            break;
        }

        pageRankScores = newPageRankScores;
    }

    // Display PageRank scores
    cout << "\nPageRank Scores:\n";
    for (const auto& entry : pageRankScores)
    {
        cout << entry.first << ": " << entry.second << endl;
    }
}

int main()
{
    const char* filename = "1.txt";

    vector<string> mainWebsites = {
        "https://www.tofugu.com/learn-japanese/",
        "https://github.com/",
        "https://codeforces.com/",
        "https://www.youtube.com/",
        "https://www.cud.ac.ae/",
        "https://leetcode.com/problemset/all/"
    };

    vector<thread> threads;
    for (size_t i = 0; i < mainWebsites.size(); ++i)
    {
        threads.emplace_back(dfs_crawler, mainWebsites[i].c_str(), filename, i + 1);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    // Calculate PageRank
    calculate_pagerank();

    // Compare ranks and assign positions only for main websites
    vector<pair<string, int>> rankings;
    for (const auto& entry : websiteRanking)
    {
        auto it = find(mainWebsites.begin(), mainWebsites.end(), entry.first);
        if (it != mainWebsites.end())
        {
            rankings.emplace_back(entry);
        }
    }

    sort(rankings.begin(), rankings.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    cout << "\nWebsite Ranking:\n";
    for (size_t i = 0; i < rankings.size(); ++i)
    {
        cout << i + 1 << "st Position: " << rankings[i].first << "  Number of Hyperlinks Found: " << rankings[i].second << endl;
    }

    // Print the total number of websites crawled by all threads
    cout << "\nTotal Number of Websites Crawled by All Threads: " << totalWebsitesCrawled << endl;

    return 0;
}

