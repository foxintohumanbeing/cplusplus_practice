
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "backtest.h""

std::vector<double> read_close_prices(const std::string& file_path){
        std::vector<double> close_prices;
        std::ifstream file(file_path);

        if (!file.is_open()){
                std::cerr<<"could not open the file:"<< file_path;
                return close_prices;
        }

        std::string line;
        std::getline(file,line);
        /*从输入的文件流file中读取第一行，并将其存储在字符串line中*/
        std::stringstream title_stream(line);
        std::string column_name;
        int index = 0;
        int close_price_index = -1;
        while (std::getline(title_stream,column_name,',')){
                if (column_name == "close"){
                        close_price_index = index;
                        break;
                }
                ++index;
        }

        if (close_price_index == -1) {
        std::cerr << "Column 'close_prices' not found in the file.\n";
        return close_prices;
        } 

        while (std::getline(file,line)){
                std::stringstream line_stream(line);
                std::string value;
                for (int i = 0; i <= close_price_index;++i){
                        std::getline(line_stream,value,',');
                }
                close_prices.push_back(std::stod(value));
        } 
        file.close();
        return close_prices;

}

double daily_return(double close_price_today,double close_price_yesterday){
        return (close_price_today-close_price_yesterday)/close_price_yesterday;
}

double momentum_factor(const std::vector<double>& close_prices, int look_back_period){
        double total_return = 0.0;
        for (int i=close_prices.size()-1;i>=close_prices.size()-look_back_period+1;--i){
                total_return += daily_return(close_prices[i],close_prices[i-1]);
        }

        return total_return/look_back_period;   
}

int main(){
        std::vector<double> close_prices = read_close_prices("ADA-USD.csv");
        std::cout << "close values: [";
        for (size_t i = 0; i < close_prices.size(); ++i) {
        std::cout << close_prices[i];
        if (i < close_prices.size() - 1) {
                std::cout << ", ";
        }
        }
        std::cout << "]\n";

        int look_back_period = 30;
        std::vector<double> momentum_values;

        for (int i = close_prices.size()-look_back_period;i >= 0;--i){
                std::vector<double> window(close_prices.begin() + i, close_prices.begin() + i + look_back_period);
                double momentum = momentum_factor(window, look_back_period);
                momentum_values.push_back(momentum);
                std::cout << "Momentum for window starting at index " << i << ": " << momentum << "\n";
                //construnct vectors
        }
        return 0;
}