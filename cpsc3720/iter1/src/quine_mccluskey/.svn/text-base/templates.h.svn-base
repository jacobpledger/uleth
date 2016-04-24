#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <ostream>

template<typename MapKey_t, typename MapVal_t> std::set<MapKey_t> Get_Set_Of_Map_Keys(const std::map<MapKey_t, MapVal_t> &source_map);
template<typename Data_t> std::set<Data_t> Set_Difference(const std::set<Data_t> &set_1, const std::set<Data_t> &set_2);
template<typename Data_t> std::set<Data_t> Set_Union(const std::set<Data_t> &set_1, const std::set<Data_t> &set_2);
template<typename Data_t> std::set<Data_t> Set_Intersection(const std::set<Data_t> &set_1, const std::set<Data_t> &set_2);
template<typename Data_t> std::set<Data_t> Set_Symmetric_Difference(const std::set<Data_t> &set_1, const std::set<Data_t> &set_2);
template<typename SubsetData_t> std::set<SubsetData_t> Union_Set_Subsets(const typename std::set<std::set<SubsetData_t> > &container);

template<typename Data_t> std::ostream & operator<<(std::ostream &stream, const std::vector<Data_t> &container);
template<typename Data_t> std::ostream & operator<<(std::ostream &stream, const std::set<Data_t> &container);
template<typename Data1_t, typename Data2_t> std::ostream & operator<<(std::ostream &stream, const std::map<Data1_t, Data2_t> &container);
template<typename Data1_t, typename Data2_t> std::ostream & operator<<(std::ostream &stream, const std::pair<Data1_t, Data2_t> &container);

template<typename MapKey_t, typename MapVal_t>
std::set<MapKey_t> Get_Set_Of_Map_Keys(const std::map<MapKey_t, MapVal_t> &source_map)
{
    std::set<MapKey_t> function_result;

    for(typename std::map<MapKey_t, MapVal_t>::const_iterator source_iter = source_map.begin(); source_iter != source_map.end(); ++source_iter)
    {
        function_result.insert(function_result.end(), source_iter->first);
    }

    return function_result;
}

template<typename Data_t>
std::set<Data_t> Set_Difference(const std::set<Data_t> &set_1, const std::set<Data_t> &set_2)
{
    std::set<Data_t> function_result;

    set_difference(set_1.begin(), set_1.end(), set_2.begin(), set_2.end(), inserter(function_result, function_result.begin()));

    return function_result;
}

template<typename Data_t>
std::set<Data_t> Set_Union(const std::set<Data_t> &set_1, const std::set<Data_t> &set_2)
{
    std::set<Data_t> function_result;

    set_union(set_1.begin(), set_1.end(), set_2.begin(), set_2.end(), inserter(function_result, function_result.begin()));

    return function_result;
}

template<typename Data_t>
std::set<Data_t> Set_Intersection(const std::set<Data_t> &set_1, const std::set<Data_t> &set_2)
{
    std::set<Data_t> function_result;

    set_intersection(set_1.begin(), set_1.end(), set_2.begin(), set_2.end(), inserter(function_result, function_result.begin()));

    return function_result;
}

template<typename Data_t>
std::set<Data_t> Set_Symmetric_Difference(const std::set<Data_t> &set_1, const std::set<Data_t> &set_2)
{
    std::set<Data_t> function_result;

    set_symmetric_difference(set_1.begin(), set_1.end(), set_2.begin(), set_2.end(), inserter(function_result, function_result.begin()));

    return function_result;
}

template<typename SubsetData_t>
std::set<SubsetData_t> Union_Set_Subsets(const std::set<std::set<SubsetData_t> > &container)
{
    std::vector<SubsetData_t> subset_elements;

    for(typename std::set<std::set<SubsetData_t> >::const_iterator container_iter = container.begin(); container_iter != container.end(); ++container_iter)
    {
        subset_elements.insert(subset_elements.end(), container_iter->begin(), container_iter->end());
    }

    return std::set<SubsetData_t>(subset_elements.begin(), subset_elements.end());
}



template<typename Data_t>
std::ostream & operator<<(std::ostream &stream, const std::vector<Data_t> &container)
{
    stream << '(';

    bool first_element_has_been_output = false;

    for(typename std::vector<Data_t>::const_iterator element = container->begin(); element != container->end(); ++element)
    {
        // output ", " only between adjacent elements
        if(first_element_has_been_output)
            stream << ", ";
        else
            first_element_has_been_output = true;

        stream << *element;
    }

    stream << ')';

    return stream;
}

template<typename Data_t>
std::ostream & operator<<(std::ostream &stream, const std::set<Data_t> &container)
{
    stream << '(';

    bool first_element_has_been_output = false;

    for(typename std::set<Data_t>::const_iterator element = container->begin(); element != container->end(); ++element)
    {
        // output ", " only between adjacent elements
        if(first_element_has_been_output)
            stream << ", ";
        else
            first_element_has_been_output = true;

        stream << *element;
    }

    stream << ')';

    return stream;
}

template<typename Data1_t, typename Data2_t>
std::ostream & operator<<(std::ostream &stream, const std::map<Data1_t, Data2_t> &container)
{
    stream << '(';

    bool first_element_has_been_output = false;

    for(typename std::map<Data1_t, Data2_t>::const_iterator element = container->begin(); element != container->end(); ++element)
    {
        // output ", " only between adjacent elements
        if(first_element_has_been_output)
            stream << ", ";
        else
            first_element_has_been_output = true;

        stream << '[' << element->first << "] = " << element->second;
    }

    stream << ')';

    return stream;
}

template<typename Data1_t, typename Data2_t>
std::ostream & operator<<(std::ostream &stream, const std::pair<Data1_t, Data2_t> &container)
{
    return stream << '<' << container.first << ", " << container.second << '>';
}

#endif
