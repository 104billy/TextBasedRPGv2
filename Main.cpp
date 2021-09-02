#include <iostream>
#include <windows.h>
#include <algorithm>
#include <string> 

void HUD();
void Combat();
void CombatHUD();
void Move();
void CreateEnemy();
void LevelUp();
void lootEnemy();

std::string name = " ", race = " ";
int level = 0, xp = 0, health = 0, totalHealth = 0, maxHealth = 0, nextLevel = 0, heal = 0, medKits = 0, accuracy = 0;        // if you do not set these the value becomes undefined. Reassignment happens in the main funcion
int enemyHP = 0, enemyXP = 0, enemyLVL = 0;

std::string playerRace[] = { "human", "soldier", "marksman"};
std::string enemyName[4] = { "Wolf", "Bandit", "Witch", "Demon" };
int currentEnemyName = 4;
std::string currentEnemy = " ";
bool isSoldier = false;

int main()
{
    level = 1;
    xp = 0;
    nextLevel = 76;
    health = 100;
    accuracy = 1;
    medKits = 5;
    totalHealth = health;
    maxHealth = totalHealth; 





    // basic character creation for the player
    std::cout << "Enter Your Character's Name: ";
    std::cin >> name;

    std::cout << "Choose Your Character's Class: \n";
    std::cout << "Human,\n";  // default values
    std::cout << "Soldier,\n";  // high armor, low health, lower accuracy
    std::cout << "Marksman\n";  // high accuracy, no armor, default health
    std::cin >> race;

    std::for_each(race.begin(), race.end(), [](char& c)
        {
            c = ::tolower(c);
        });

    for (int i = 0; i < sizeof(playerRace); i++)   // Add accuracy and armor maybe!
    {
        if (race == "human")
        {
            accuracy = 70;
            health == 100;
            break;
        }
        else if (race == "soldier")
        {
            isSoldier = true;
            accuracy = 60;
            health == 120;
            break;
        }
        else if (race == "marksman")
        {
            accuracy = 80;
            health == 100;
            break;
        }
        else
        {
            std::cout << "Invalid Choice, Using Default: Human....\n";
            Sleep(1000);
            race = "human";
            health = 100;
            accuracy = 60;
            break;
        }
    }


    // Animation

    
    for (int i = 0; i <= 2; i++)
    {
        std::cout << "Creating Character\n";
        Sleep(400);
        system("cls");
        
        std::cout << "Creating Character.\n";
        Sleep(400);
        system("cls");

        std::cout << "Creating Character..\n";
        Sleep(400);
        system("cls");

        std::cout << "Creating Character...\n";
        Sleep(400);
        system("cls");

        std::cout << "Creating Character....\n";
        Sleep(700);
        system("cls");

    };
    
    name[0] = toupper(name[0]);
    race[0] = toupper(race[0]);
    
    HUD();
    Move();
    
    system("pause>0");
    return 0;
}

void HUD() 
{
    LevelUp();
    Sleep(2000);
    system("cls");
    std::cout << "------------------------------------\n" << "Class: " << race << "\n------------------------------------\n" << "Name: " << name << "      " << "Health : " << 
        totalHealth << "\nLevel: " << level
        << "        " << "XP: " << xp << "/" << nextLevel << std::endl << "\n# of Med Kits: " << medKits << std::endl <<
        "\n------------------------------------" << "\nChoose Your Next Decision: " << "\n------------------------------------\n" << std::endl;
    Move();
}

void CombatHUD()
{
    Sleep(500);
    system("cls");
    std::cout << "Name: " << name << "      |       " << currentEnemy << "\nHealth: " << totalHealth << "     |       Enemy Health: " <<
        enemyHP << "\n Level: " << level << "       |       Enemy Level: " << enemyLVL << std::endl;
}

void Combat()
{
    CombatHUD();
    char playerAttack;
    int playerDamage = 32 * level / 2;
    int enemyAttack = 12 * level / 2;

    if (enemyHP >= 1 && totalHealth >= 1)
    {
        std::cout << "\n";
        std::cout << "1: Attack\n";
        std::cout << "2: Block\n";
        std::cout << "3: Escape\n";
        std::cout << "\n";
        std::cin >> playerAttack;
            
        if (isSoldier)
        {
            playerDamage = playerDamage + (level * 2);
        }


        if (playerAttack == '1')
        {
            //Attack
            
            int tempPlayer = rand() % 100 + 1;
            int acc = rand() % 100 + 1;

            if (tempPlayer >= 85 && acc <= accuracy)
            {
                playerDamage = playerDamage * 2;
                std::cout << "You Dealt a Critical Hit for x2 Damage!!\n";
                Sleep(100);
            }

            if (acc <= accuracy)
            {
                std::cout << "Attacking.... You did: " << playerDamage << " to the " << currentEnemy << std::endl;
                enemyHP = enemyHP - playerDamage;
                Sleep(100);
            }
            else
            {
                std::cout << "You Missed!";
                Sleep(500);
            }

            
            Sleep(1000);
            CombatHUD();

            if (enemyHP >= 1)
            {
                int tempEnemy = rand() % 100 + 1;

                if(isSoldier && acc >= 50) 
                {
                    std::cout << "Your Armor Blocked Some Damage.\n";
                    enemyAttack = enemyAttack / 2;
                }

                if (tempEnemy >= 85)
                {
                    enemyAttack = enemyAttack * 2;
                    std::cout << currentEnemy << " Dealt a Critical Hit for x2 Damage!!\n";
                    Sleep(100);
                }
                // currently enemies can't miss, but if the player is a soldier they may have their attack strength divided by 2
                std::cout << "\n";
                std::cout << "The enemy is attacking....\n";
                totalHealth = totalHealth - enemyAttack;
                std::cout << "The enemy inflicted " << enemyAttack << "\nRemaining HP: " << totalHealth << std::endl;
                // Change to function because we type it a lot!

                if (totalHealth <= 0)
                {
                    totalHealth = 0;
                }
            }
            else if (enemyHP <= 0)
            {
                enemyHP = 0;
            }
            Sleep(1000);
            Combat();
        }
            else if (playerAttack == '2')
            {
                std::cout << "You Attempt to Block....\n";
                int i = rand() % 100 + 1;
                if (i >= 30)
                {
                    std::cout << "You successfully blocked the attack!\n";
                    heal = level * 10 / 2;
                    std::cout << "You Gained " << heal << "hp" << std::endl;
                    totalHealth = totalHealth + heal;
                    Sleep(1000);
                    Combat();
                }
                else
                {
                    std::cout << "You failed to block the attack!\n";
                    totalHealth -= enemyAttack;
                    std::cout << "You Lost " << enemyAttack << "hp attempting to block!";
                    Sleep(1000);
                    Combat();
                }
            }
            else if (playerAttack == '3')
            { // Escape
                std::cout << "You attempt to flee\n";
                int x = rand() % 100 + 1;
                if (x >= 50)
                {
                    std::cout << "You successfully escaped the enemy!\n";
                    Sleep(1000);
                    HUD();
                }
                else
                {
                    totalHealth -= enemyAttack + 5;
                    std::cout << "You tried to escape but failed and lost " << enemyAttack << "hp\n";
                    std::cout << "Health: " << totalHealth;
                    Sleep(1000);
                    Combat();
                }
            }
            else
            {
                std::cout << "Incorrect Number\n";
                system("cls");
                Combat();
            }
    } 

    if (totalHealth <= 1)
    {
        system("cls");
        std::cout << "You Died. \n You were level: " << level << " and were killed by a: Level " << enemyLVL << " " << currentEnemy << std::endl;
        Sleep(5000);
        exit(0);
    }

    if (enemyHP <= 1)
    {
        xp = xp + enemyXP;

        std::cout << "\n";
        std::cout << "The " << currentEnemy << " has been killed" << std::endl;
        std::cout << "You gained " << enemyXP << "xp. Well Done! \n";
        std::cout << std::endl; 
        Sleep(1000);
        std::cout << "You search the enemy for medicine....\n";
        Sleep(1000);
        std::cout << std::endl; 
        lootEnemy();
        LevelUp();
        Sleep(1500);
        HUD();
    }
}

void Move() 
{
    char choice;

    std::cout << "1: Continue\n";
    std::cout << "2: Rest/Heal\n";
    std::cout << "3: Go Back\n";
    std::cout << "\n------------------------------------\n";

    std::cin >> choice;

    if (choice == '1')
    {
            int temp = rand() % 100 + 1;    // 10 in computer terms is 99 so we add 1. This is a random number generator!
            std::cout << "You Continue on Your Journey....\n";
            if (temp >= 50)
            {                               // Enemy encounter here!
                CreateEnemy();
                std::string tempName = enemyName[rand() % currentEnemyName];
                std::cout << "A " << tempName << " suddenly appears from the bush! Prepare to Fight!\n";
                currentEnemy = tempName;
                Sleep(1000);
                Combat();
            }
            std::cout << "You Found Nothing While Exploring....\n";
            Sleep(1000);
            HUD();
    }
        else if (choice == '2')
        {
                if (totalHealth <= 99 && medKits >= 1)
                {
                    std::cout << "You take a knee to patch yourself up....\n";
                    totalHealth += 10 * level;
                    medKits--;
                    std::cout << "Med Kits Remaining: " << medKits << std::endl;
                    std::cout << "Total Health: " << totalHealth << std::endl;
                    Sleep(1000);
                }
                else if (totalHealth <= 99 && medKits < 1)
                {
                    totalHealth += 2 * level;
                    std::cout << "After resting for a moment you feel strong and ready to fight! \nTotal Health: " << totalHealth << std::endl;
                    Sleep(1000);
                }
                else
                {
                    std::cout << "You are ready to fight!";
                    Sleep(1000);
                }
                    HUD();
        }
            else if (choice == '3')
            {
                int temp = rand() % 100 + 1;    // 10 in computer terms is 99 so we add 1. This is a random number generator!
                    if (temp >= 50)
                    {                               // Enemy encounter here!
                        CreateEnemy();
                        std::string tempName = enemyName[rand() % currentEnemyName]; 
                        std::cout << "A " << tempName << " suddenly appears from the bush! Prepare to Fight!\n";
                        currentEnemy = tempName;
                        Sleep(1000);
                        Combat();
                    }
                        else
                        {
                            std::cout << "You Retrace Your Steps....\n";
                            Sleep(1000);
                            HUD();
                        }
            }
                else 
                {
                    std::cout << "Incorrect Number\n";
                    Sleep(1000);
                    HUD();
                    Move();  
                }
}

void CreateEnemy()
{
    enemyHP = 30;

    enemyLVL = (rand() % 3) + level;  
    
    enemyHP = (rand() % 50) * enemyLVL;

    enemyXP = enemyHP;

    if (enemyXP == 0)
    {
        CreateEnemy();
    }

    if (enemyHP == 0)
    {
        CreateEnemy();
    }

    if (enemyLVL == 0)
    {
        CreateEnemy();
    }
}

void LevelUp()
{
    if (xp >= nextLevel)
    {
        level++;
        nextLevel = nextLevel * 3 / 2;
        totalHealth = totalHealth + 20;
        maxHealth = totalHealth;
        std::cout << "You Levelled Up!\n";
        std::cout << "Current Level: " << level << std::endl;
        Sleep(1000);
        HUD(); 
    }
}

void lootEnemy()
{
    int loot = rand() % 100 + 1;

    if (loot >= 85)
    {
        medKits++;
        std::cout << "You Found x1 Med Kit!\n";
        Sleep(1000);
    }
    else
    {
    std::cout << "You searched the " << currentEnemy << " but found nothing.\n";
    }
}