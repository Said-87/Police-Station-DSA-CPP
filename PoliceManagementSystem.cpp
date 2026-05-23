

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
#include <algorithm>
#include <sstream>
#include <fstream>
using namespace std;

/*************************************************************
                    DATA MODELS (STRUCTS)
*************************************************************/

// Officer Structure (Linked List Node)
struct Officer
{
    int id;
    string name;
    int serviceYears;
    string station;
    Officer *next;

    Officer(int i, string n, int sy, string st)
    {
        id = i;
        name = n;
        serviceYears = sy;
        station = st;
        next = NULL;
    }
};

// Criminal Structure (For HashTable & BST)
struct Criminal
{
    int id;
    string name;
    string area;
    int threatLevel; // BST Key
    Criminal *left;
    Criminal *right;

    Criminal(int i, string n, string a, int t)
    {
        id = i;
        name = n;
        area = a;
        threatLevel = t;
        left = right = NULL;
    }
};

// FIR Structure (Queue Node)
struct FIR
{
    int firNumber;
    string applicantName;
    string crimeType;
    FIR *next;
};

// Evidence Structure (Stack Records)
struct Evidence
{
    string evidenceDetails;
    Evidence *next;
};

/*************************************************************
            GLOBAL HEAD POINTERS FOR DATA STRUCTURES
*************************************************************/

Officer *officerHead = NULL;   // Linked List Head
Criminal *criminalRoot = NULL; // BST Root
Evidence *evidenceTop = NULL;  // Stack Top

queue<FIR *> firQueue; // FIR Queue

const int HASH_SIZE = 10;                // Hash Table Size
vector<Criminal *> hashTable[HASH_SIZE]; // Hash Table (Chaining)

/*************************************************************
            HASH FUNCTION (FOR CRIMINAL ID LOOKUP)
*************************************************************/
int hashFunction(int id)
{
    return id % HASH_SIZE;
}

/*************************************************************
 *** SUPPORT FUNCTIONS (BASIC UI & INPUT HANDLING)
 *************************************************************/

// Clears input buffer
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void header(string title)
{
    cout << "\n\n============================================\n";
    cout << "           " << title << "\n";
    cout << "============================================\n";
}
/*************************************************************
                LINKED LIST: OFFICER MANAGEMENT
*************************************************************/

// Insert Officer at End of Linked List
void addOfficer()
{
    header("Add New Officer");

    int id, serviceYears;
    string name, station;

    cout << "Enter Officer ID: ";
    cin >> id;
    clearInput();
    cout << "Enter Officer Name: ";
    getline(cin, name);
    cout << "Enter Service Years: ";
    cin >> serviceYears;
    clearInput();
    cout << "Enter Station Name: ";
    getline(cin, station);

    Officer *newOfficer = new Officer(id, name, serviceYears, station);

    if (officerHead == NULL)
    {
        officerHead = newOfficer;
    }
    else
    {
        Officer *temp = officerHead;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newOfficer;
    }

    cout << "\n✔ Officer Added Successfully!\n";
}

// Display All Officers
void displayOfficers()
{
    header("All Registered Police Officers");

    if (officerHead == NULL)
    {
        cout << " No officers found.\n";
        return;
    }

    Officer *temp = officerHead;
    while (temp != NULL)
    {
        cout << "\nOfficer ID: " << temp->id;
        cout << "\nName: " << temp->name;
        cout << "\nService Years: " << temp->serviceYears;
        cout << "\nStation: " << temp->station;
        cout << "\n-----------------------------------\n";
        temp = temp->next;
    }
}

// Count Total Officers
void countOfficers()
{
    header("Total Officer Count");

    int count = 0;
    Officer *temp = officerHead;
    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    cout << "Total Number of Officers: " << count << endl;
}

/*************************************************************
                HASH TABLE: CRIMINAL MANAGEMENT
*************************************************************/

// Insert Criminal into Hash Table
void addCriminal()
{
    header("Add Criminal Record");

    int id, threat;
    string name, area;

    cout << "Enter Criminal ID: ";
    cin >> id;
    clearInput();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Area: ";
    getline(cin, area);
    cout << "Enter Threat Level (1-10): ";
    cin >> threat;

    Criminal *c = new Criminal(id, name, area, threat);

    int idx = hashFunction(id);
    hashTable[idx].push_back(c);

    cout << "\n Criminal Added to Hash Table Successfully!\n";
}

// Search Criminal by ID
void searchCriminalByID()
{
    header("Search Criminal by ID");

    int id;
    cout << "Enter Criminal ID: ";
    cin >> id;

    int idx = hashFunction(id); // Get hash index
    bool found = false;

    for (auto c : hashTable[idx]) // Traverse chain
    {
        if (c->id == id) // Check if ID matches
        {
            cout << "\n Criminal Found\n";
            cout << "ID: " << c->id << "\nName: " << c->name
                 << "\nArea: " << c->area
                 << "\nThreat Level: " << c->threatLevel << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\n Criminal Not Found!\n";
}

// Display Criminals by Area
void showCriminalsByArea()
{
    header("Criminals by Area");

    string area;
    clearInput(); // clear buffer
    cout << "Enter Area Name: ";
    getline(cin, area);

    bool found = false;
    for (int i = 0; i < HASH_SIZE; i++)
    {
        for (auto c : hashTable[i]) // Traverse each chain
        {
            if (c->area == area)
            {
                cout << "\nID: " << c->id
                     << " | Name: " << c->name
                     << " | Threat Level: " << c->threatLevel << endl;
                found = true;
            }
        }
    }

    if (!found)
        cout << "\n No Criminals Found in This Area.\n";
}
/*************************************************************
                    QUEUE: FIR MANAGEMENT
*************************************************************/

void registerFIR()
{
    header("Register New FIR");

    FIR *f = new FIR();
    cout << "Enter FIR Number: ";
    cin >> f->firNumber;
    clearInput();
    cout << "Enter Applicant Name: ";
    getline(cin, f->applicantName); // read full line
    cout << "Enter Crime Type: ";
    getline(cin, f->crimeType); // read full line

    f->next = NULL;
    firQueue.push(f);

    cout << "\n FIR Registered and Added to Queue Successfully!\n";
}

void processFIR()
{
    header("Process Next FIR");

    if (firQueue.empty())
    {
        cout << "\n No FIRs to Process.\n";
        return;
    }

    FIR *f = firQueue.front();
    firQueue.pop();

    cout << "\n Processing FIR:\n";
    cout << "FIR No: " << f->firNumber
         << "\nApplicant: " << f->applicantName
         << "\nCrime: " << f->crimeType << endl;

    delete f;
}
/*************************************************************
                    STACK: EVIDENCE STORAGE
*************************************************************/

void addEvidence()
{
    header("Add Evidence to Stack");

    string detail;
    clearInput();
    cout << "Enter Evidence Description: ";
    getline(cin, detail);

    Evidence *e = new Evidence();
    e->evidenceDetails = detail;
    e->next = evidenceTop;
    evidenceTop = e;

    cout << "\n Evidence Stored Successfully!\n";
}

void removeEvidence()
{
    header("Remove Last Evidence");

    if (evidenceTop == NULL)
    {
        cout << " No Evidence Exists.\n";
        return;
    }

    Evidence *temp = evidenceTop;
    evidenceTop = evidenceTop->next;

    cout << "\n Removed Evidence: " << temp->evidenceDetails << endl;
    delete temp;
}
/*************************************************************
        BINARY SEARCH TREE: THREAT LEVEL MANAGEMENT
*************************************************************/

// Insert Node into BST (by threatLevel)
Criminal *insertBST(Criminal *root, Criminal *c)
{
    if (root == NULL)
        return c;

    if (c->threatLevel < root->threatLevel)
        root->left = insertBST(root->left, c);

    else if (c->threatLevel > root->threatLevel)
        root->right = insertBST(root->right, c);

    // If same threat level → compare ID to avoid duplicates & loop
    else
    {
        if (c->id < root->id)
            root->left = insertBST(root->left, c);
        else if (c->id > root->id)
            root->right = insertBST(root->right, c);
        else
            return root; // SAME ID → do not re-insert
    }

    return root;
}

// Build BST from Hash Table
void buildBSTFromHash()
{
    criminalRoot = NULL;

    for (int i = 0; i < HASH_SIZE; i++)
    {
        for (Criminal *c : hashTable[i])
        {
            criminalRoot = insertBST(criminalRoot, c);
        }
    }
}

// Display Criminals in Ascending Order
void inorderBST(Criminal *root)
{
    if (root == NULL)
        return;

    inorderBST(root->left);

    cout << "ID: " << root->id
         << " | Name: " << root->name
         << " | Threat: " << root->threatLevel
         << endl;

    inorderBST(root->right);
}

// Find Min Threat Level
Criminal *minThreat(Criminal *root)
{
    if (!root)
        return NULL;
    while (root->left)
        root = root->left;
    return root;
}

// Find Max Threat Level
Criminal *maxThreat(Criminal *root)
{
    if (!root)
        return NULL;
    while (root->right)
        root = root->right;
    return root;
}

// Wrapper Actions
void showSortedCriminals()
{
    header("Criminals Sorted by Threat");
    buildBSTFromHash(); // Rebuild BST
    inorderBST(criminalRoot);
}

void showMinThreat()
{
    header("Lowest Threat Criminal");
    buildBSTFromHash();
    Criminal *c = minThreat(criminalRoot);
    if (!c)
        cout << " No Data.\n";
    else
        cout << " Lowest Threat: " << c->name << " (Level " << c->threatLevel << ")\n";
}

void showMaxThreat()
{
    header("Highest Threat Criminal");
    buildBSTFromHash();
    Criminal *c = maxThreat(criminalRoot);
    if (!c)
        cout << " No Data.\n";
    else
        cout << " Highest Threat: " << c->name << " (Level " << c->threatLevel << ")\n";
}
/*************************************************************
                MERGE SORT (OFFICERS)
*************************************************************/

Officer *merge(Officer *left, Officer *right)
{
    if (!left)
        return right;
    if (!right)
        return left;

    if (left->serviceYears <= right->serviceYears)
    {
        left->next = merge(left->next, right);
        return left;
    }
    else
    {
        right->next = merge(left, right->next);
        return right;
    }
}

void split(Officer *source, Officer **front, Officer **back)
{
    Officer *fast = source->next;
    Officer *slow = source;

    while (fast)
    {
        fast = fast->next;
        if (fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void mergeSort(Officer **headRef)
{
    Officer *head = *headRef;
    if (!head || !head->next)
        return;

    Officer *a, *b;
    split(head, &a, &b);

    mergeSort(&a);
    mergeSort(&b);

    *headRef = merge(a, b);
}

void sortOfficersByService()
{
    header("Officers Sorted by Service Years (Ascending)");
    mergeSort(&officerHead);
    displayOfficers();
}
/*************************************************************
            QUICK SORT (CRIMINALS BY NAME)
*************************************************************/

vector<Criminal *> criminalList;

int partitionQS(int low, int high)
{
    string pivot = criminalList[high]->name;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (criminalList[j]->name < pivot)
        {
            i++;
            swap(criminalList[i], criminalList[j]);
        }
    }
    swap(criminalList[i + 1], criminalList[high]);
    return i + 1;
}

void quickSort(int low, int high)
{
    if (low < high)
    {
        int pi = partitionQS(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void sortCriminalsByName()
{
    header("Criminals Sorted by Name");

    criminalList.clear();
    for (int i = 0; i < HASH_SIZE; i++)
        for (auto c : hashTable[i])
            criminalList.push_back(c);

    if (criminalList.empty())
    {
        cout << "No Criminals Found.\n";
        return;
    }

    quickSort(0, criminalList.size() - 1);

    for (auto c : criminalList)
    {
        cout << c->name << " | ID: " << c->id << " | Threat: " << c->threatLevel << endl;
    }
}
/*************************************************************
            MAX HEAP (EMERGENCY CASE PRIORITY)
*************************************************************/

struct EmergencyCase
{
    int priority;
    string caseDetails;

    bool operator<(const EmergencyCase &e) const // Overload <
    {
        return priority < e.priority; // Max Heap
    }
};

priority_queue<EmergencyCase> emergencyPQ;

void addEmergencyCase()
{
    header("Add Emergency Case");

    EmergencyCase e;
    cout << "Enter Case Priority (1=Low, 10=Extreme): ";
    cin >> e.priority;
    clearInput();
    cout << "Describe Case: ";
    getline(cin, e.caseDetails);

    emergencyPQ.push(e);
    cout << "⚠ Emergency Case Added to Priority Queue!\n";
}

void handleHighestPriority()
{
    header("Handle Critical Case");

    if (emergencyPQ.empty())
    {
        cout << "No Emergency Cases Pending.\n";
        return;
    }

    EmergencyCase top = emergencyPQ.top();
    emergencyPQ.pop();

    cout << " Handling Case: " << top.caseDetails
         << " | Priority: " << top.priority << endl;
}
/*************************************************************
                    GRAPH: POLICE STATIONS
*************************************************************/

int stationCount = 0;
vector<string> stations;
vector<vector<int>> distanceMatrix; // adjacency matrix

void addStation()
{
    header("Add Police Station");
    string name;
    clearInput();
    cout << "Enter Station Name: ";
    getline(cin, name);

    stations.push_back(name);
    stationCount++;

    // Expand matrix
    for (auto &row : distanceMatrix) // add column to each row
        row.push_back(0);
    distanceMatrix.push_back(vector<int>(stationCount, 0));

    cout << "✔ Station Added Successfully!\n";
}

void addRoute()
{
    header("Add Route Between Stations");
    if (stationCount < 2)
    {
        cout << "At least 2 stations required.\n";
        return;
    }

    for (int i = 0; i < stationCount; i++)
        cout << i << " → " << stations[i] << endl;

    int a, b, dist;
    cout << "\nSelect Station A Index: ";
    cin >> a;
    cout << "Select Station B Index: ";
    cin >> b;
    cout << "Enter Distance: ";
    cin >> dist;

    distanceMatrix[a][b] = distanceMatrix[b][a] = dist;
    cout << "Route Added Successfully!\n";
}

void showStations()
{
    header("Station Network");
    for (int i = 0; i < stationCount; i++)
    {
        cout << i << " → " << stations[i] << endl;
    }
}
int minDistance(vector<int> dist, vector<bool> visited)
{
    int minVal = INT_MAX, minIndex = -1;
    for (int i = 0; i < stationCount; i++)
    {
        if (!visited[i] && dist[i] <= minVal)
        {
            minVal = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void findShortestRoute()
{
    header("Shortest Route (Dijkstra)");

    if (stationCount < 2)
    {
        cout << " Not enough stations.\n";
        return;
    }

    int src;
    cout << "Enter Source Station Index: ";
    cin >> src;

    if (src < 0 || src >= stationCount)
    {
        cout << " Invalid Station Index\n";
        return;
    }

    vector<int> dist(stationCount, INT_MAX);
    vector<bool> visited(stationCount, false);
    dist[src] = 0;

    for (int i = 0; i < stationCount - 1; i++)
    {
        int u = minDistance(dist, visited);

        // 🚨 SAFETY CHECK - No reachable nodes left
        if (u == -1)
            break;

        visited[u] = true;

        for (int v = 0; v < stationCount; v++)
        {
            if (!visited[v] && distanceMatrix[u][v] > 0 &&
                dist[u] != INT_MAX &&
                dist[u] + distanceMatrix[u][v] < dist[v])
            {
                dist[v] = dist[u] + distanceMatrix[u][v];
            }
        }
    }

    cout << "\n Shortest Distance From Station " << stations[src] << ":\n";
    for (int i = 0; i < stationCount; i++)
    {
        if (dist[i] == INT_MAX)
            cout << " " << stations[i] << " is NOT reachable\n";
        else
            cout << "-> " << stations[i] << " : " << dist[i] << " km\n";
    }
}

/*************************************************************
                FILE HANDLING (CSV FORMAT)
*************************************************************/

void saveOfficersToFile()
{
    ofstream file("officers.csv", ios::trunc); // overwrite
    if (!file.is_open())
    {
        cout << " Error: Could not open officers.csv for writing\n";
        return;
    }

    Officer *temp = officerHead;
    while (temp)
    {
        file << temp->id << ","
             << temp->name << ","
             << temp->serviceYears << ","
             << temp->station << "\n";
        temp = temp->next;
    }

    file.close();
    cout << " Officers Saved to officers.csv\n";
}

void loadOfficersFromFile()
{
    header("Loading Officers from File");

    ifstream file("officers.csv"); // read mode
    if (!file.is_open())
    {
        cout << " officers.csv Not Found\n";
        return;
    }

    officerHead = NULL; // clear previous data

    string line;
    while (getline(file, line)) // read each line
    {
        if (line.empty())
            continue; // skip empty lines

        stringstream ss(line);                 // create a stringstream from the line
        string idStr, name, yearsStr, station; // temp vars

        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, yearsStr, ',');
        getline(ss, station, ',');

        int id = stoi(idStr);       // convert to int
        int years = stoi(yearsStr); // convert to int

        Officer *newOfficer = new Officer(id, name, years, station);

        // Insert at end (your method)
        if (!officerHead)
        {
            officerHead = newOfficer;
        }
        else
        {
            Officer *temp = officerHead;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newOfficer;
        }
    }

    cout << " Officers Loaded Successfully from officers.csv\n";
}

/*************************************************************
                FILE HANDLING — CRIMINALS
*************************************************************/

void saveCriminalsToFile()
{
    header("Saving Criminals to File");
    ofstream file("criminals.csv");
    if (!file)
    {
        cout << " File Error\n";
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++)
    {
        for (auto c : hashTable[i])
        {
            file << c->id << ","
                 << c->name << ","
                 << c->area << ","
                 << c->threatLevel << "\n";
        }
    }

    cout << " Criminals Saved → criminals.csv\n";
}

void loadCriminalsFromFile()
{
    header("Loading Criminals from File");

    ifstream file("criminals.csv");
    if (!file)
    {
        cout << " criminals.csv Not Found\n";
        return;
    }

    // Reset previous data
    for (int i = 0; i < HASH_SIZE; i++)
        hashTable[i].clear();
    criminalRoot = NULL;

    string line, name, area;
    int id, threat;

    while (getline(file, line))
    {
        if (line == "")
            continue;

        stringstream ss(line);
        getline(ss, line, ',');
        id = stoi(line);
        getline(ss, name, ',');
        getline(ss, area, ',');
        getline(ss, line, ',');
        threat = stoi(line);

        Criminal *c = new Criminal(id, name, area, threat);
        int idx = hashFunction(id);
        hashTable[idx].push_back(c);
    }

    buildBSTFromHash(); // rebuild BST!

    cout << " Criminals Loaded (Hash + BST Ready)\n";
}
/*************************************************************
                FILE HANDLING — FIR QUEUE
*************************************************************/

void saveFIRToFile()
{
    header("Saving FIR History");

    ofstream file("fir.csv", ios::app); // append
    if (!file)
    {
        cout << " File Error\n";
        return;
    }

    queue<FIR *> tempQ = firQueue;

    while (!tempQ.empty())
    {
        FIR *f = tempQ.front();
        tempQ.pop();

        file << f->firNumber << ","
             << f->applicantName << ","
             << f->crimeType << "\n";
    }

    cout << " FIRs Saved → fir.csv\n";
}
void loadFIRFromFile()
{
    header("Loading FIRs from File");

    ifstream file("fir.csv");
    if (!file.is_open())
    {
        cout << " fir.csv not found, skipping FIR load.\n";
        return;
    }

    // Clear existing queue
    while (!firQueue.empty())
    {
        firQueue.pop();
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string firStr, name, crime;

        getline(ss, firStr, ',');
        getline(ss, name, ',');
        getline(ss, crime, ',');

        FIR *f = new FIR();
        f->firNumber = stoi(firStr);
        f->applicantName = name;
        f->crimeType = crime;
        f->next = NULL;

        firQueue.push(f);
    }

    file.close();
    cout << " FIRs Loaded from fir.csv\n";
}
/*************************************************************
                FILE HANDLING — STATIONS
*************************************************************/

void saveStationsToFile()
{
    ofstream file("stations.csv");
    if (!file)
    {
        cout << " File Error\n";
        return;
    }

    for (string s : stations)
        file << s << "\n";

    cout << " Stations Saved → stations.csv\n";
}

void loadStationsFromFile()
{
    ifstream file("stations.csv");
    if (!file.is_open())
    {
        cout << "⚠️ stations.csv not found, skipping.\n";
        return;
    }

    stations.clear();
    stationCount = 0;

    string name;
    while (getline(file, name))
    {
        if (!name.empty())
        {
            stations.push_back(name);
            stationCount++;
        }
    }
    file.close();

    // 🛠️ Rebuild matrix fresh
    distanceMatrix = vector<vector<int>>(stationCount, vector<int>(stationCount, 0));

    cout << "✔ Stations Loaded: " << stationCount << endl;
}

/*************************************************************
                FILE HANDLING — ROUTES
*************************************************************/

void saveRoutesToFile()
{
    ofstream file("routes.csv");
    if (!file)
    {
        cout << " File Error\n";
        return;
    }

    for (int i = 0; i < stationCount; i++)
    {
        for (int j = i + 1; j < stationCount; j++)
        {
            if (distanceMatrix[i][j] > 0)
            {
                file << stations[i] << ","
                     << stations[j] << ","
                     << distanceMatrix[i][j] << "\n";
            }
        }
    }

    cout << " Routes Saved → routes.csv\n";
}

void loadRoutesFromFile()
{
    ifstream file("routes.csv");
    if (!file.is_open())
        return;

    string a, b, line;
    int dist;

    while (getline(file, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);

        getline(ss, a, ',');
        getline(ss, b, ',');
        ss >> dist;

        int ai = find(stations.begin(), stations.end(), a) - stations.begin();
        int bi = find(stations.begin(), stations.end(), b) - stations.begin();

        if (ai < stationCount && bi < stationCount)
        {
            distanceMatrix[ai][bi] = dist;
            distanceMatrix[bi][ai] = dist;
        }
    }

    cout << "✔ Routes Loaded.\n";
}

/*************************************************************
                    MAIN MENU
*************************************************************/

int main()
{
    // ✅ Auto load data when program starts
    loadOfficersFromFile();
    loadCriminalsFromFile();
    loadStationsFromFile();
    loadRoutesFromFile();
    loadFIRFromFile();

    int choice;

    while (true)
    {
        cout << "\n======= Police Management System =======" << endl;
        cout << "\n================ Linked List ================\n";
        cout << "1. Add Officer\n2. Display Officers\n3. Count Officers\n";

        cout << "================ Hash Table ================\n";
        cout << "4. Add Criminal\n5. Search Criminal by ID\n6. Show Criminals by Area\n";

        cout << "================ Queue (FIR) ================\n";
        cout << "7. Register FIR\n8. Process FIR\n";

        cout << "================ Stack ================\n";
        cout << "9. Add Evidence\n10. Remove Evidence\n";

        cout << "================ BST ================\n";
        cout << "11. Lowest Threat\n12. Highest Threat\n13. Sorted Threat\n";

        cout << "================ Sorting ================\n";
        cout << "14. Sort Officers by Service Years\n15. Sort Criminals by Name\n";

        cout << "================ Heap ================\n";
        cout << "16. Add Emergency Case\n17. Handle Critical Case\n";

        cout << "================ Graph ================\n";
        cout << "18. Add Station\n19. Add Route\n20. Show Stations\n21. Shortest Route\n";

        // cout << "================ File ================\n";
        // cout << "22. Save Officers\n23. Load Officers\n";

        cout << "================ Save/Load All Data ================\n";
        cout << "22. Save All Data\n23. Load All Data\n";

        cout << "================ Exit ================\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addOfficer();
            break;
        case 2:
            displayOfficers();
            break;
        case 3:
            countOfficers();
            break;

        case 4:
            addCriminal();
            break;
        case 5:
            searchCriminalByID();
            break;
        case 6:
            showCriminalsByArea();
            break;

        case 7:
            registerFIR();
            break;
        case 8:
            processFIR();
            break;

        case 9:
            addEvidence();
            break;
        case 10:
            removeEvidence();
            break;

        case 11:
            showMinThreat();
            break;
        case 12:
            showMaxThreat();
            break;
        case 13:
            showSortedCriminals();
            break;

        case 14:
            sortOfficersByService();
            break;
        case 15:
            sortCriminalsByName();
            break;

        case 16:
            addEmergencyCase();
            break;
        case 17:
            handleHighestPriority();
            break;

        case 18:
            addStation();
            break;
        case 19:
            addRoute();
            break;
        case 20:
            showStations();
            break;
        case 21:
            findShortestRoute();
            break;

        case 22:
            saveOfficersToFile();
            saveCriminalsToFile();
            saveStationsToFile();
            saveRoutesToFile();
            saveFIRToFile();
            break;

        case 23:
            loadOfficersFromFile();
            loadCriminalsFromFile();
            loadStationsFromFile();
            loadRoutesFromFile();
            loadFIRFromFile();
            break;
        case 0:
            return 0;

        default:
            cout << " Invalid Choice\n";
        }
    }
    return 0;
}
