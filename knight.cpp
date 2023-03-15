#include "knight.h"

int *event = nullptr; 
string file[3];

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}
bool isPrime(int n) {
    if (n == 2) return true;
    else {
        for (int i = 2; i < n; i++) {
            if (n % i == 0) return false;
        }
    }
    return true;
}
int nextPrime(int n){
    int nextPrime = n+1;
    bool done = false;
    while (!done) {
        if (isPrime(nextPrime) == true) {
            done = true;
        }
        else nextPrime += 1;
    }
    return nextPrime;
}
int fibonacci(int n) {
    if (n == 0) return 0;
    else if (n == 1 || n == 2) return 1;
    else if (n > 2) return fibonacci(n - 1) + fibonacci(n - 2);
    else return 0;
}
void theSecondMax(int* arr, int n, int& max2_3x, int& max2_3i) {
    int arr3Number[3];
    for (int i = 0; i < 3; i++) arr3Number[i] = arr[i];
    int max1 = max(arr3Number[0], max(arr3Number[1], arr3Number[2]));
    if (arr3Number[0] != max1) {
        if (arr3Number[0] > max2_3x) {
            max2_3x = arr3Number[0];
            max2_3i = 0;
        }
    }
    if (arr3Number[1] != max1) {
        if (arr3Number[1] > max2_3x) {
            max2_3x = arr3Number[1];
            max2_3i = 1;
        }
    }
    if (arr3Number[2] != max1) {
        if (arr3Number[1] > max2_3x) {
            max2_3x = arr3Number[2];
            max2_3i = 2;
        }
    }

}
int readFile(string file_input,int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown) {
    ifstream input_file(file_input); // open the input file
    int numEvent = 0;
    if (input_file.is_open()) {
        string line;
        //Line 1:
        getline(input_file, line);
        // Read information for the knight
        istringstream iss(line);
        iss >> HP >> level >> remedy >> maidenkiss >> phoenixdown;
        // Read information for event
        getline(input_file, line); // Line 2
        istringstream iss2(line);
        istringstream ss2(line);
        int n;
        int i = 0; // So luong phan tu dong su kien
        while (iss2 >> n) {
            i++;
        }
        numEvent = i;
        event = new int[i]; // Cap phat so luong cho mang event
        for (int j = 0; j < i; j++) {
            ss2 >> event[j];
        }
        // Line 3:
        int index = 0;
        while (getline(input_file, line, ',')) {
            file[index] = line;
            index++;
        }
        //Close file
        input_file.close();
    }
    else cout << "This file is not opened!" << endl;
    return numEvent;
}
bool isMountain(int* arr, int n, int& maxVal, int& indexMax) {
    maxVal = arr[0];
    indexMax = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
            indexMax = i;
        }
    }
    if (indexMax == 0 || indexMax == (n - 1)) {
        if (indexMax == 0) {
            for (int i = 0; i < n-1; i++) {
                if (arr[i] <= arr[i + 1]) return false;
            }
        }
        else if (indexMax == n - 1) {
            for (int i = 0; i < n-1; i++) {
                if (arr[i] >= arr[i + 1]) return false;
            }
        }
    }
    else {
        for (int i = 0; i < indexMax; i++) {
            if (arr[i] >= arr[i + 1]) return false;
        }
        int pos = indexMax;
        while (pos < n - 1) {
            if (arr[pos] <= arr[pos + 1]) return false;
            pos++;
        }
        
    }
    return true;
}
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    int eventNow; // Variable to check the current event
    rescue = -1; // Continue the journey
    // Call function to read file
    int numEvent = readFile(file_input, HP, level,remedy,maidenkiss,phoenixdown);
    const int MaxHP = HP;
    bool tiny = false; // Bien ti hon
    bool Frog = false; // Bien ech
    bool Arthur;
    bool Lancelot;
    int oldLevel;
    const float baseDamage[5] = { 1,1.5,4.5,7.5,9.5 };
    int count_tiny = 0;
    int count_Frog = 0;
        // Test infor event
    // King Arthur:
    if (HP == 999) Arthur = true;
    else Arthur = false;
    // Lancelot
    if (isPrime(HP)) Lancelot = true;
    else Lancelot = false;
    //Solve all events in game:
    for (int i = 0; i < numEvent; i++) {
        eventNow = event[i];
        int b = (i + 1) % 10;
        int levelO = (i + 1) > 6 ? (b > 5 ? b : 5) : b; // Level of Enemy     
        // TH1 : Event = 0
        if (eventNow == 0) {
            rescue = 1;
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            break;
        }
        // TH2 : Event = 1 .. 5
        else if (eventNow == 1 || eventNow == 2 || eventNow == 3 || eventNow == 4 || eventNow == 5) {
            if (level > levelO || Arthur || Lancelot) level++; // Level up the knight
            else if (level == levelO);
            else {
                int damage = baseDamage[eventNow - 1] * levelO * 10;
                HP = HP - damage;
            }
            if (level > 10) level = 10;

        }
        // TH3 : Event = 6
        else if (eventNow == 6) {
            if (tiny == true || Frog == true) goto Solve;
            if ((level > levelO) || Arthur || Lancelot) {
                level += 2;
                if (level > 10)  level = 10;
            }
            else if (level == levelO);
            else {
                tiny = true;
                if (remedy >= 1) {
                    tiny = false;
                    remedy -= 1;
                }
                // If dont have remedy -> tiny == true
                else {
                    if (HP < 5) HP = 1;
                    else HP /= 5;
                }
            }

        }
        // TH4: Event = 7
        else if (eventNow == 7) {
            oldLevel = level;
            if (tiny == true || Frog == true) goto Solve;
            if ((level > levelO) || Arthur || Lancelot) {
                level += 2;
                if (level > 10)  level = 10;
            }
            else if (level == levelO);
            else {
                Frog = true;
                if (maidenkiss >= 1) {
                    Frog = false;
                    maidenkiss -= 1;
                }
                // If dont have maidenkiss -> Frog == true
                else   level = 1;
            }

        }
        // TH5 : Event = 11
        else if (eventNow == 11) {
            int n1 = ((level + phoenixdown) % 5 + 1) * 3;
            int init = 99;
            int s1 = 0;
            while (n1 > 0) {
                s1 += init;
                init -= 2;
                n1--;
            }
            HP = HP + (s1 % 100);
            HP = nextPrime(HP);
            if (HP > MaxHP) HP = MaxHP;
        }
        // TH6: Event = 12;
        else if (eventNow == 12) {
            int n = 2;
            if (HP == 1);
            else if (HP > 1) {
                while (fibonacci(n) < HP) {
                    n++;
                }
                HP = fibonacci(n);
            }

        }
        // TH7: Event form == 13
        else if (eventNow > 100) {
            string numstring = to_string(eventNow);
            if (numstring.substr(0, 2) == "13") {
                ifstream file1(file[0]); // use ifstream instead of fstream to open file for reading
                int i = 0;
                int index_mushroom = 2; // After 13
                string line; // use string instead of int for line and n variables
                int numOfElement;
                int stt = 1;
                file1 >> numOfElement;
                int numArr[numOfElement];
                getline(file1, line); // consume the first line
                while (getline(file1, line)) {
                    istringstream ss(line);
                    while (getline(ss, line, ',')) { // read into line instead of n variable
                        numArr[i] = stoi(line); // convert string to int and assign to array
                        i++;
                    }
                }
                // Now We had data file mushroom
                while (index_mushroom < numstring.length()) {
                    int maxi = 0, mini = 0;
                    int max = numArr[0];
                    int min = numArr[0];
                    // Case 1:
                    if (numstring[index_mushroom] == '1') {
                        for (int i = 1; i < numOfElement;i++) {
                            if (numArr[i] >= max) {
                                max = numArr[i];
                                maxi = i;
                            }
                            if (numArr[i] <= min) {
                                min = numArr[i];
                                mini = i;
                            }
                        }
                        //Update HP:
                        HP = HP - (maxi + mini);

                    }
                    // Case 2:
                    else if (numstring[index_mushroom] == '2') {
                        int maxVal = numArr[0];
                        int indexMax = 0;
                        bool is_Mountain = isMountain(numArr, numOfElement, maxVal, indexMax);
                        if (!is_Mountain) {
                            maxVal = -2;
                            indexMax = -3;
                        }
                        HP = HP - (maxVal + indexMax);
                    }
                    // Case 3:
                    else if (numstring[index_mushroom] == '3') {
                        int case3[numOfElement];
                        for (int i = 0; i < numOfElement; i++) {
                            case3[i] = numArr[i];
                            if (case3[i] < 0) case3[i] = -case3[i];
                            case3[i] = (17 * case3[i] + 9) % 257;
                        }
                        int maxi2 = 0, mini2 = 0;
                        int max2 = case3[0];
                        int min2 = case3[0];
                        for (int i = 1; i < numOfElement; i++) {
                            if (case3[i] >= max2) {
                                max2 = case3[i];
                                maxi2 = i;
                            }
                            if (case3[i] <= min2) {
                                min2 = case3[i];
                                mini2 = i;
                            }
                        }
                        HP = HP - (maxi2 + mini2);
                    }
                    // Case 4:
                    else if (numstring[index_mushroom] == '4') {
                        int case4[numOfElement];
                        for (int i = 0; i < numOfElement; i++) {
                            case4[i] = numArr[i];
                            if (case4[i] < 0) case4[i] = -case4[i];
                            case4[i] = (17 * case4[i] + 9) % 257;
                        }
                        int max2_3x = -5;
                        int max2_3i = -7;
                        theSecondMax(case4, numOfElement, max2_3x, max2_3i);
                        HP = HP - (max2_3x + max2_3i);
                    }
                    //After each loop:
                    if (HP > MaxHP) HP = MaxHP;
                    else if (HP < 0 && phoenixdown > 0) {
                        HP = MaxHP;
                        phoenixdown -= 1;
                    }
                    else if (HP <= 0 && phoenixdown < 1) {
                        goto Solve;
                    }
                    // Update index
                    index_mushroom++;
                }
                
            }
        }

        // TH8 Event 15 16 17
        else if (eventNow == 15 && remedy < MAX_ITEM) remedy += 1;
        else if (eventNow == 16 && maidenkiss < MAX_ITEM) maidenkiss += 1;
        else if (eventNow == 15 && phoenixdown < MAX_ITEM) phoenixdown += 1;
        
        
        //TH9 : Event 19
        else if (eventNow == 19) {
            // Just Consider First 
            if (i == 0) {
                ifstream file2(file[1]);
                int row, col;
                string line;
                file2 >> row >> col;
                int itemArray[row][col] = { 0 };
                getline(file2, line);
                int r = 0;
                while (getline(file2, line)) {
                    istringstream ss(line);
                    for (int c = 0; c < col; c++) ss >> itemArray[r][c];
                    r++;
                }
                // Update remedy, maidenkiss, phoneixdown
                for (int i = 0; i < row; i++) {
                    int count = 0;
                    for (int j = 0; j < row; j++) {
                        if (count < 3) {
                            if (itemArray[i][j] == 16) {
                                remedy += 1;
                                count++;
                            }
                            else if (itemArray[i][j] == 17) {
                                maidenkiss += 1;
                                count++;
                            }
                            else if (itemArray[i][j] == 18) {
                                phoenixdown += 1;
                                count++;
                            }
                        }
                    }
                }
                if (remedy > MAX_ITEM) remedy = MAX_ITEM;
                if (maidenkiss > MAX_ITEM) maidenkiss = MAX_ITEM;
                if (phoenixdown > MAX_ITEM) phoenixdown = MAX_ITEM;
                goto Solve;
            }

        }
        else if (eventNow == 99) {
            if (level == 10 || (level >= 8 && Lancelot) || Arthur) level = 10;
            else {
                rescue = 0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
        }


        // Event : Merlin 18

    Solve:
        // tiny
        if (tiny == true && HP <= 0 && phoenixdown > 0) {
            tiny = false;
            phoenixdown -= 1;
            HP = MaxHP;
            count_tiny = 0;
        }
        else if (tiny == true && HP > 0) count_tiny += 1;
        if (count_tiny == 4) {
            tiny == false;
            count_tiny = 0;
            HP *= 5;
            if (HP > MaxHP) HP = MaxHP;
        }
        // Frog
        if (Frog == true && maidenkiss < 1 && count_Frog < 4) {
            count_Frog += 1;
        }
        else if (Frog == true && maidenkiss < 1 && count_Frog == 4) level = oldLevel;

        // Check result game if all event over
        if (HP <= 0 && phoenixdown <= 0) {
            rescue = 0;
            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            break;
        }
        else if (HP <= 0 && phoenixdown > 0) {
            phoenixdown -= 1;
            HP = MaxHP;
        }
        if (HP > 0 && i + 1 == numEvent) rescue = 1;
            // Display the knight 's index
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        
    }
    delete[] event;
}


