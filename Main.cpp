#include <iostream>
#include <vector>
#include <string>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경

    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) {
            std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                std::cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }

    //레시피 검색 기능 (물약이름 인자 -> 재료 출력)
    void searchRecipe_potionName(std::string searchName) {
        for (int i = 0; i < recipes.size(); i++) {
            if (searchName == recipes[i].potionName) {
                std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
                std::cout << "  > 필요 재료:  ";
                for (int j = 0; j < recipes[i].ingredients.size(); j++) {
                    if (j != recipes[i].ingredients.size() - 1) {
                        std::cout << recipes[i].ingredients[j] << ", ";
                    }
                    else {
                        std::cout << recipes[i].ingredients[j] << std::endl;
                    }
                }
                return;
            }
        }
        std::cout << "일치하는 물약이 존재하지 않습니다." << std::endl;
        return;
    }

    //레시피 검색 기능 (재료 -> 물약 -> searchRecipe_potionName 함수 호출)
    void searchRecipe_ingredientName(std::string searchName) {
        bool isExist = false; //재료 사용하는 레시피 존재여부 판별용.
        for (int i = 0; i < recipes.size(); i++) {
            for (int j = 0; j < recipes[i].ingredients.size(); j++) {
                if (searchName == recipes[i].ingredients[j]) {
                    searchRecipe_potionName(recipes[i].potionName);
                    isExist = true;
                }
            }
        }
        if (isExist == false) {
            std::cout << "해당 재료를 사용한 물약이 존재하지 않습니다." << std::endl;
        }
    }
};

int main() {
    AlchemyWorkshop myWorkshop;

    while (true) {
        std::cout << "?? 연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 레시피 검색" << std::endl;
        std::cout << "4. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }

        else if (choice == 3) {
            int choice_3;
            std::string searchName;
            std::cout << "검색 종류를 선택해주세요." << std::endl;
            std::cout << "1. 물약 검색" << std::endl;
            std::cout << "2. 재료 검색" << std::endl;
            while (true) {
                std::cout << "번호 입력 : ";
                std::cin >> choice_3;
                if (choice_3 == 1) {
                    std::cout << "검색할 물약 이름 입력 : ";
                    std::cin >> searchName;
                    myWorkshop.searchRecipe_potionName(searchName);
                    break;
                }
                else if (choice_3 == 2) {
                    std::cout << "검색할 재료 이름 입력 : ";
                    std::cin >> searchName;
                    myWorkshop.searchRecipe_ingredientName(searchName);
                    break;
                }
                else {
                    std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
                }
            }
        }

        else if (choice == 4) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;
        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}