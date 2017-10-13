#include <stdio.h>
#include <cs50.h>

bool check_sum(long long card_number);
string get_company(long long card_number);

int main(void)
{
    printf("Number: ");
    long long input = get_long_long();
    bool card_valid = check_sum(input);
    
    if(card_valid)
    {
        string brand = get_company(input);
        printf("%s\n", brand);
    } 
    else 
    {
        printf("INVALID\n");
    }
}

bool check_sum(long long card_number)
{
    int sum = 0;
    
    for(int i=0; i <= 16; i++){
        if(i % 2){
            int c_num = card_number % 10 * 2;
            if(c_num > 9){
                while(c_num)
                {
                    sum += c_num % 10;
                    c_num /= 10;
                }
            } 
            else 
            {
                sum += c_num;
            }
        }
        else 
        {
            sum += card_number %10;
        }
        card_number /=10;
    }
    
    if(sum % 10 == 0)
    {
        return true;
    } 
    else 
    {
        return false;
    }
}

string get_company(long long card_number){
    
    int id_num = card_number / 100000000000000;
    
    if(id_num / 10 == 4){
        return "VISA";
    }
    
    else if(id_num > 50 && id_num < 56){
        return "MASTERCARD";
    }
    
    else {
        return "AMEX";
    }
}
