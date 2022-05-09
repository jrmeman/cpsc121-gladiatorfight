// Justin Meman
// CPSC 121 Lab 6
// 03/22/2019
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <fstream>
using namespace std;

// Structure for the stats of a gladiator
struct Gladiator{
  string name;
  int maxHP;
  int evasion;
  int crit;
  int minDam;
  int damRange;
};

// Structure for fight stats
struct Fight{
  int damage;
  int critDam;
  int timesMissed;
};

Gladiator getInfo(); // Stats for Gladiator Prototype
char showStats(Gladiator); // Show/reroll stats Prototype
Fight takeTurn(Gladiator, Gladiator&); // Fight prototype
void pause(); // Pause Prototype

int main()
{
  srand(time(NULL)); // Allows stats to be truly random
  char again; // Variable to allow reroll of gladiator stats
  bool cont; // Allows fight to continue until someone dies
  char restart = 'Y'; // Allows program to restart
  char rematch = 'Y'; // Allows gladiators to have a rematch

  cout << "Welcome to the Gladiator Ring!" << endl;
  Gladiator glad1; // Holds 1st gladiator stats
  Gladiator glad2; // Holds 2nd gladiator stats
  Fight glad1Stats;
  Fight glad2Stats;
  // Declaring counters for each gladiator
  int glad1Dam, glad1Crit, glad1Ev;
  int glad2Dam, glad2Crit, glad2Ev;
  // Placeholders for each fighter's HP for a rematch
  int glad1RematchHP, glad2RematchHP;

// Loop for the program
  do{
// Loop for the 1st Gladiator
    do{
      glad1 = getInfo();

      again = showStats(glad1);
    } while(again == 'N' || again == 'n');
    cout << "The first fighter has been set!" << endl << endl;
    glad1RematchHP = glad1.maxHP;

// Loop for the 2nd Gladiator
    do{
      glad2 = getInfo();

      again = showStats(glad2);
    } while(again == 'N' || again == 'n');
    cout << "The second fighter has been set!" << endl;
    glad2RematchHP = glad2.maxHP;

// Fight Code Block
    do{ // Do While Loop allows for rematch
        glad1.maxHP = glad1RematchHP;
        glad2.maxHP = glad2RematchHP;
        glad1Dam = glad1Crit = glad1Ev = 0; // Counters for first gladiator
        glad2Dam = glad2Crit = glad2Ev = 0; // Counters for second gladiator

        cout << endl <<"The fight will now commence!" << endl;
        cin.ignore();
        pause();


        do{ // Do While Loop for the fight
          cont = true; // Allows the fight to continue

          glad1Stats = takeTurn(glad1, glad2);
          glad1Dam += glad1Stats.damage;
          glad1Crit += glad1Stats.critDam;
          glad1Ev += glad1Stats.timesMissed;
          cout << endl;

// If Statement allows the 2nd gladiator to fight if they're still alive
        if(glad2.maxHP > 0){
          glad2Stats = takeTurn(glad2, glad1);
          glad2Dam += glad2Stats.damage;
          glad2Crit += glad2Stats.critDam;
          glad2Ev += glad2Stats.timesMissed;
          cout << endl;
        }
// If Statement declares end of fight and end Do While Loop
        if(glad1.maxHP <= 0 || glad2.maxHP <= 0){
          cout << "A fighter has fallen!" << endl;
          cont = false;
        }
        else
          pause(); // Allows program to "pause" to see each turn
        } while(cont);

// If Statement to declare stats if 1st gladiator wins
        if(glad1.maxHP > glad2.maxHP){
          cout << "The winner is: " << glad1.name << endl;
          cout << "Total Damage: " << glad1Dam << endl;
          cout << "Crit Damage: " << glad1Crit << endl;
          cout << "Times Missed: " << glad1Ev << endl;
        }
// If Statement to declare stats if 2nd gladiator wins
        else if(glad2.maxHP > glad1.maxHP){
          cout << "The winner is: " << glad2.name << endl;
          cout << "Total Damage: " << glad2Dam << endl;
          cout << "Crit Damage: " << glad2Crit << endl;
          cout << "Times Missed: " << glad2Ev << endl;
        }
// Fall back if something in the program goes wrong
        else{
          cout << "Something went wrong!" << endl;
          cout << "Please restart the program" << endl;
        }

        cout << endl << "Would you like a rematch with the same fighters? (Y/N) ";
        cin >> rematch;

      } while(rematch == 'Y' || rematch == 'y');

      cout << "Would you like to restart the program with new fighters? (Y/N) ";
      cin >> restart;
  } while(restart == 'Y' || restart == 'y');

  cout << "Thanks for using the program!" << endl;

  return 0;
}

// Sets the stats for each gladiator
Gladiator getInfo(){
  Gladiator tempGlad;

  cout << "Enter a fighter name: ";
  cin >> tempGlad.name;

  int hpPoints[] = {150, 200, 250};
  int evCrit[] = {5, 10, 15};

  int hpIndex = rand() % 3;
  tempGlad.maxHP = hpPoints[hpIndex];

  int evCritIndex1 = rand() % 3;
  int evCritIndex2 = rand() % 3;
  tempGlad.evasion = evCrit[evCritIndex1];
  tempGlad.crit = evCrit[evCritIndex2];

  tempGlad.minDam = 8 + (rand() % 6);
  tempGlad.damRange = 16 + (rand() % 6);
  return tempGlad;
}

// Displays each gladiator's stats
char showStats(Gladiator glad){
  char tempAgain;

  cout << endl;
  cout << glad.name << endl;
  cout << "Max HP: " << glad.maxHP << endl;
  cout << "Evasion: " << glad.evasion << "%" << endl;
  cout << "Critical Chance: " << glad.crit << "%" << endl;
  cout << "Min. Damage: " << glad.minDam << endl;
  cout << "Damage Range: " << glad.damRange << endl;
  cout << "Possible Damage: " << glad.minDam << " - ";
  cout << glad.minDam + glad.damRange << endl;
  cout << "Do you accept your gladiator? (Y/N) ";
  cin >> tempAgain;

  return tempAgain;
}

// Fight function
Fight takeTurn(Gladiator glad1, Gladiator &glad2){
  Fight fightStats;
  fightStats.damage = fightStats.critDam = fightStats.timesMissed = 0;

  if((1 + rand()%100) <= glad1.crit){
    fightStats.damage = 2 * (glad1.minDam + (rand()%glad1.damRange));
    fightStats.critDam = fightStats.damage;
    fightStats.timesMissed = 0;
    glad2.maxHP -= fightStats.damage;
    cout << "A critical hit!" << endl;
    cout << glad1.name << " deals " << fightStats.damage << " damage!" << endl;
    cout << glad2.name << "\'s HP: " << glad2.maxHP << endl;
  }
  else if((1 + rand()%100) <= glad2.evasion){
    fightStats.timesMissed += 1;
    fightStats.critDam = fightStats.damage = 0;
    cout << glad1.name << "\'s attack missed!" << endl;
    cout << glad1.name << " deals no damage!" << endl;
    cout << glad2.name << "\'s HP: " << glad2.maxHP << endl;
  }
  else{
    fightStats.damage = glad1.minDam + (rand()%glad1.damRange);
    glad2.maxHP -= fightStats.damage;
    fightStats.critDam = fightStats.timesMissed = 0;
    cout << glad1.name << " strikes " << glad2.name << endl;
    cout << glad1.name << " deals " << fightStats.damage << " damage!" << endl;
    cout << glad2.name << "\'s HP: " << glad2.maxHP << endl;
  }

  return fightStats;
}

// Pause Function
void pause(){
  cout << "Press [Enter] to continue";
  cin.get();
  cout << endl;
}