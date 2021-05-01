//
// Created by evgen on 01.05.2021.
//

#ifndef TEMPERATURE_DISTRIBUTION_VECROT_H
#define TEMPERATURE_DISTRIBUTION_VECROT_H

vector<double>operator-(const vector<double>& vec1, const vector<double>& vec2)
{
    if (vec1.size() != vec2.size()) {
        std::string s1 = "(" + std::to_string(vec1.size()) + " | " + std::to_string(vec2.size()) + ")";
        std::string error = "Invalid size of vectors (operation \"-\")" + s1;
        throw std::runtime_error(error);
    }
    vector<double> res;
    res.reserve(vec1.size());
    for (int i = 0; i < vec2.size(); ++i)
        res.push_back(vec1[i] - vec2[i]);
    return res;
}

ostream &operator<<(ostream& os, const vector<double>& vector)
{
    for (double i : vector)
        os << "|| " << i << " ||"<<std::endl;
    os << std::endl;
    return os;
}

double norm(const vector<double>& a){
    double sum = 0;
    for(double i : a){
        sum += i*i;
    }
    return sqrt(sum);
}
#endif //TEMPERATURE_DISTRIBUTION_VECROT_H
