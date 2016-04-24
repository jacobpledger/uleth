#include "quinemccluskey.h"
#include <algorithm>
using namespace std;

Implicants_t Quine_McCluskey(TruthTableString_t truth_table_string)
{
    Implicants_t implicants = Generate_Implicants_From_Truth_Table_String(truth_table_string);

    ImplicantsWithSameNumberOfOnes_t grouped_implicants = Group_Implicants_By_Number_Of_Ones_In_Binary_Representation(implicants);

//    cout << "\nGrouped Implicants\n";
//    cout << grouped_implicants;

    Implicants_t prime_implicants = Gather_Prime_Implicants(grouped_implicants);

//    cout << "\nPrime Implicants\n";
//    cout << prime_implicants;

    return Get_Minimum_Set_Of_Prime_Implicants(prime_implicants, truth_table_string);
}

Implicants_t Generate_Implicants_From_Truth_Table_String(string truth_table_string)
{
    Minterms_t minterms = Generate_Minterms_From_Truth_Table_String(truth_table_string);

//    cout << "Minterms" << endl;
//    cout << minterms;

    Implicants_t implicants = Convert_Minterms_Into_Implicants(minterms);

//    cout << "Equivalent Implicants:" << endl;
//    cout << implicants << endl;

    return implicants;
}

Minterms_t Generate_Minterms_From_Truth_Table_String(string truth_table_string)
{
    unsigned int bits_per_truth_table_row = Log_Base_2(truth_table_string.length());

//	create a key-value container of key-value containers, map<int(number_of_ones), map<set<int(row_number)>, vector<pseudobinary> > >, function_result
    Minterms_t minterms;

    for(string::size_type truth_table_row_number = 0; truth_table_row_number < truth_table_string.length(); ++truth_table_row_number)
    {
//		if the row's expected value is not false
        if('0' != truth_table_string.at(truth_table_row_number))
        {
            //store the row number and binary representation of the row in function_result
            minterms.insert(make_pair(truth_table_row_number, Generate_Binary_String(truth_table_row_number, bits_per_truth_table_row)));
        }
    }

    return minterms;
}

// an implicant is a covering of one or more minterms, so we need to convert each minterm's row number into a single entry in a set of row numbers
Implicants_t Convert_Minterms_Into_Implicants(Minterms_t minterms)
{
    Implicants_t implicants;

    for(Minterms_t::iterator minterm = minterms.begin(); minterm != minterms.end(); ++minterm)
    {
        SetOfRowNumbers_t set_of_row_numbers;
        set_of_row_numbers.insert(minterm->first);

        implicants.insert(make_pair(set_of_row_numbers, minterm->second));
    }

    return implicants;
}

ImplicantsWithSameNumberOfOnes_t Group_Implicants_By_Number_Of_Ones_In_Binary_Representation(Implicants_t implicants)
{
    ImplicantsWithSameNumberOfOnes_t grouped_implicants;

    for(Implicants_t::iterator implicant = implicants.begin(); implicant != implicants.end(); ++implicant)
    {
//		store the number of ones in the binary representation of the row number, number_of_ones
        NumberOfOnes_t number_of_ones_in_implicant_binary_representation = Number_Of_Ones_In_Binary_String(implicant->second);
        grouped_implicants[number_of_ones_in_implicant_binary_representation].insert(*implicant);
    }

    return grouped_implicants;
}

int Number_Of_Ones_In_Binary_String(const BinaryString_t &binstr)
{
    return count(binstr.begin(), binstr.end(), '1');
}

Implicants_t Gather_Prime_Implicants(ImplicantsWithSameNumberOfOnes_t grouped_implicants)
{
    Implicants_t prime_implicants;

    bool progress_was_made;

    do
    {
        // returns a pair of Implicants_t, the first being the results of successful combination, the second being those implicants that could not be combined
        ImplicantCombinationResult_t combination_results = Combine_Implicants_Differing_By_Single_Bit(grouped_implicants);

        grouped_implicants = combination_results.first;

        prime_implicants.insert(combination_results.second.begin(), combination_results.second.end());

        if(!combination_results.first.empty())
        {
            progress_was_made = true;
        }
        else
        {
            progress_was_made = false;
        }
    }
    while(progress_was_made);

    return prime_implicants;
}

/*! returns an ordered pair, where the first element is the result of combining the old implicants, and the second element contains all old_implicants that could not be combined */
ImplicantCombinationResult_t Combine_Implicants_Differing_By_Single_Bit(ImplicantsWithSameNumberOfOnes_t grouped_implicants)
{
    ImplicantsWithSameNumberOfOnes_t combined_implicants;
    Implicants_t unused_implicants;

    //! Insert all the of the (uncategorized by number_of_ones) implicants in old_implicants into our list of unused implicants
    for(ImplicantsWithSameNumberOfOnes_t::iterator implicant_group = grouped_implicants.begin(); implicant_group != grouped_implicants.end(); ++implicant_group)
    {
        unused_implicants.insert(implicant_group->second.begin(), implicant_group->second.end());
    }

    ImplicantsWithSameNumberOfOnes_t::iterator end_iter = Get_Next_To_Last_Iterator(grouped_implicants.begin(), grouped_implicants.end());

    //! for each index, number_of_ones, in old_implicants (except the last index)
    for(ImplicantsWithSameNumberOfOnes_t::iterator last_iter = grouped_implicants.begin(); last_iter != end_iter; ++last_iter)
    {
        NumberOfOnes_t number_of_ones = last_iter->first;

        //! if the key (number_of_ones + 1) exists in old_implicants
        ImplicantsWithSameNumberOfOnes_t::iterator next_iter = grouped_implicants.find(number_of_ones + 1);

        if(next_iter != grouped_implicants.end())
        {
            //! for each key-value pair, (lower_row_number, lower_pseudo_rep), in minterms[number_of_ones]
            for(Implicants_t::iterator lower_iter = last_iter->second.begin(); lower_iter != last_iter->second.end(); ++lower_iter)
            {
                //! for each key-value pair, (upper_row_number, upper_pseudo_rep), in minterms[number_of_ones + 1]
                for(Implicants_t::iterator upper_iter = next_iter->second.begin(); upper_iter != next_iter->second.end(); ++upper_iter)
                {
                    //! if lower_pseudo_rep and upper_pseudo_rep differ by only one pseudobit
                    if(Binary_Strings_Differ_By_Single_Bit(lower_iter->second, upper_iter->second))
                    {
                        BinaryString_t binary_string = Combine_Binary_Strings_Differing_By_Single_Bit(lower_iter->second, upper_iter->second);

                        // union the row numbers of the two sets
                        SetOfRowNumbers_t combined_row_numbers(Set_Union(lower_iter->first, upper_iter->first));

                        //! remove the source implicants from the unused_implicants container
                        unused_implicants.erase(lower_iter->first);
                        unused_implicants.erase(upper_iter->first);

                        //! insert the combined_implicant into the combined_implicants container
                        combined_implicants[number_of_ones].insert(make_pair(combined_row_numbers, binary_string));
                    }
                }
            }
        }
    }

    return make_pair(combined_implicants, unused_implicants);
}

BinaryString_t Combine_Binary_Strings_Differing_By_Single_Bit(BinaryString_t string_1, BinaryString_t string_2)
{
    string binary_string(string_1);

    BinaryString_t::size_type bit_offset = Get_Offset_Of_Differing_Bit(string_1, string_2);

    binary_string.at(bit_offset) = 'X';

    return binary_string;
}

bool Binary_Strings_Differ_By_Single_Bit(BinaryString_t string_1, BinaryString_t string_2)
{
    bool found_different_bit = false;

    for(BinaryString_t::size_type bit_offset = 0; bit_offset < string_1.length(); ++bit_offset)
    {
        if(string_1.at(bit_offset) != string_2.at(bit_offset))
        {
            if(found_different_bit)
            {
                return false;
            }
            else
            {
                found_different_bit = true;
            }
        }
    }

    return true;
}

BinaryString_t::size_type Get_Offset_Of_Differing_Bit(BinaryString_t string_1, BinaryString_t string_2)
{
    for(BinaryString_t::size_type bit_offset = 0; bit_offset < string_1.length(); ++bit_offset)
    {
        if(string_1.at(bit_offset) != string_2.at(bit_offset))
        {
            return bit_offset;
        }
    }

    return string_1.length();
}

Implicants_t Gather_Essential_Prime_Implicants(Implicants_t implicants, TruthTableString_t truth_table_string)
{
    Implicants_t essential_prime_implicants;
    // union all implicant row numbers into set_of_row_numbers
    SetOfRowNumbers_t prime_implicant_row_numbers(Remove_Dont_Cares(Union_All_Implicant_Row_Number_Sets(implicants), truth_table_string));
//    cout << '\n' << prime_implicant_row_numbers << '\n';

    for(SetOfRowNumbers_t::iterator set_iter = prime_implicant_row_numbers.begin(); set_iter != prime_implicant_row_numbers.end(); ++set_iter)
    {
        int match_count = 0;
        Implicants_t::iterator last_match_iter;

        for(Implicants_t::iterator imp_iter = implicants.begin(); imp_iter != implicants.end(); ++imp_iter)
        {
            if(imp_iter->first.find(*set_iter) != imp_iter->first.end())
            {
                ++match_count;
                last_match_iter = imp_iter;
            }
        }

        if(match_count == 1)
        {
            essential_prime_implicants.insert(*last_match_iter);
        }
    }

    SetOfRowNumbers_t prime_implicant_rows_covered_by_essential_prime_implicants(Remove_Dont_Cares(Union_All_Implicant_Row_Number_Sets(essential_prime_implicants), truth_table_string));

    SetOfRowNumbers_t uncovered_prime_implicant_row_numbers = Set_Difference(prime_implicant_row_numbers, prime_implicant_rows_covered_by_essential_prime_implicants);

//    cout << "Uncovered Row Numbers: " << uncovered_prime_implicant_row_numbers << endl;

    return essential_prime_implicants;
}

ImplicantsWithSameNumberOfOnes_t::iterator Get_Next_To_Last_Iterator(ImplicantsWithSameNumberOfOnes_t::iterator begin_iter, ImplicantsWithSameNumberOfOnes_t::iterator end_iter)
{
    ImplicantsWithSameNumberOfOnes_t::iterator function_result;

    ImplicantsWithSameNumberOfOnes_t::iterator last_iter = begin_iter; // this will mark the last key in minterms
    ImplicantsWithSameNumberOfOnes_t::iterator next_iter = last_iter;

    while(next_iter != end_iter)
    {
        last_iter = next_iter;
        ++next_iter;
    }

    return last_iter;
}

//! given two maps, returns all entries in map_1 where each entry's index is not found in map_2's index set)
Implicants_t Map_Difference(Implicants_t map_1, Implicants_t map_2)
{
    Implicants_t function_result;

    for(Implicants_t::iterator iter = map_1.begin(); iter != map_1.end(); ++iter)
    {
        if(map_2.find(iter->first) == map_2.end())
        {
            function_result.insert(*iter);
        }
    }

    return function_result;
}

set<SetOfRowNumbers_t> Get_Implicants_Sets(const Implicants_t &implicants)
{
    set<SetOfRowNumbers_t> function_result;

    for(Implicants_t::const_iterator iter = implicants.begin(); iter != implicants.end(); ++iter)
    {
        function_result.insert(function_result.end(), iter->first);
    }

    return function_result;
}

Implicants_t Get_Minimum_Set_Of_Prime_Implicants(Implicants_t prime_implicants, TruthTableString_t truth_table_string)
{
    // returns Implicants_t containing all essential prime implicants in prime_implicants
    Implicants_t essential_prime_implicants(Gather_Essential_Prime_Implicants(prime_implicants, truth_table_string));
//    cout << "\nEssential Prime Implicants\n";
//    cout << essential_prime_implicants << endl;

    // returns Implicants_t containing all unessential prime implicants in prime_implicants (those prime implicants that are not essential prime implicants)
    Implicants_t unessential_prime_implicants(Map_Difference(prime_implicants, essential_prime_implicants));
//    cout << "\nUnessential Prime Implicants\n";
//    cout << unessential_prime_implicants;

    SetOfRowNumbers_t rows_covered_by_essential_prime_implicants(Union_All_Implicant_Row_Number_Sets(essential_prime_implicants));
//    cout << "\nRows Covered By Essential Prime Implicants\n";
//    cout << rows_covered_by_essential_prime_implicants << endl;

    Implicants_t uncovered_unessential_prime_implicants;

    for(Implicants_t::iterator unessential_iter = unessential_prime_implicants.begin(); unessential_iter != unessential_prime_implicants.end(); ++unessential_iter)
    {
        SetOfRowNumbers_t uncovered_unessential_prime_implicant_rows(Set_Difference(unessential_iter->first, rows_covered_by_essential_prime_implicants));

        if(!uncovered_unessential_prime_implicant_rows.empty())
        {
            uncovered_unessential_prime_implicants.insert(make_pair(uncovered_unessential_prime_implicant_rows, unessential_iter->second));
        }
    }

//    cout << "\nUncovered Unessential Prime Implicants\n";
//    cout << uncovered_unessential_prime_implicants;

//    cout << "\nReverse Implicant Lookup\n";
    map<BinaryString_t, SetOfRowNumbers_t> reverse_implicant_lookup;

    for(Implicants_t::iterator iter = prime_implicants.begin(); iter != prime_implicants.end(); ++iter)
    {
        reverse_implicant_lookup.insert(make_pair(iter->second, iter->first)); // the key/value relation is two way, so this should work
//        cout << iter->second << ", " << iter->first << endl;
    }

    SumOfProducts_t minimum_products(Petricks_Method(uncovered_unessential_prime_implicants));

    Implicants_t minimum_set_of_prime_implicants(essential_prime_implicants);

    if(!minimum_products.empty())
    {
        // just grab the first minimum_products product
        for(SumOfProductsProduct_t::iterator final_minterms = minimum_products.begin()->begin(); final_minterms != minimum_products.begin()->end(); ++final_minterms)
        {
            minimum_set_of_prime_implicants.insert(make_pair(reverse_implicant_lookup[*final_minterms], *final_minterms));
        }
    }

    return minimum_set_of_prime_implicants;
}

// given a bunch of unessential prime implicants (with don't care rows removed), this will return a sum of products of the implicant values (not the row numbers)
SumOfProducts_t Petricks_Method(Implicants_t unessential_prime_implicants)
{
    SetOfRowNumbers_t minterms(Union_All_Implicant_Row_Number_Sets(unessential_prime_implicants));

    ProductOfSums_t product_of_sums;

    // convert unessential_prime_implicants into form (P0+P1+P2)&(P3+P5)&(P7+P8)
    // minterms... (top of table)
    for(SetOfRowNumbers_t::iterator minterm_iter = minterms.begin(); minterm_iter != minterms.end(); ++minterm_iter)
    {
        ProductOfSumsSum_t product_of_sums_sum;
        // P variables (left of table)
        for(Implicants_t::iterator implicant_iter = unessential_prime_implicants.begin(); implicant_iter != unessential_prime_implicants.end(); ++implicant_iter)
        {
            product_of_sums_sum.push_back(implicant_iter->second);
        }

        product_of_sums.push_back(product_of_sums_sum);
        product_of_sums_sum.clear();
    }

    // convert product_of_sums_term into form (P0&P3&P7)+(P0&P3&P8)+(P0&P5&P7)+... etc by calculating all cartesian products of the product of sum terms
    SumOfProducts_t sum_of_products = Convert_Petricks_Product_Of_Sums_To_Sum_Of_Products(product_of_sums);

    SumOfProducts_t minimum_sum_of_products_products;

    if(!sum_of_products.empty())
    {
        SumOfProductsProduct_t::size_type minimum_size = sum_of_products.begin()->size();

        // insert only the least costly products into minimum_sum_of_products_products
        for(SumOfProducts_t::iterator products_iter = sum_of_products.begin(); products_iter != sum_of_products.end(); ++products_iter)
        {
            // if this product group is smaller than our currently stored groups
            if(products_iter->size() < minimum_size)
            {
                minimum_sum_of_products_products.clear();
                minimum_sum_of_products_products.push_back(*products_iter);
                minimum_size = products_iter->size();
            }
            else if(products_iter->size() == minimum_size)
            {
                minimum_sum_of_products_products.push_back(*products_iter);
            }
        }
    }

    return minimum_sum_of_products_products;
}

vector<vector<BinaryString_t> > Convert_Petricks_Product_Of_Sums_To_Sum_Of_Products(vector<vector<BinaryString_t> > product_of_sums)
{
    vector<vector<BinaryString_t> > old_sum_of_products;

    // for each sequence of summed terms in product_of_sums
    for(vector<vector<BinaryString_t> >::iterator pos_product_iter = product_of_sums.begin(); pos_product_iter != product_of_sums.end(); ++pos_product_iter)
    {
        // create a sequence of
        vector<vector<BinaryString_t> > new_sum_of_products;

        // sort and remove any duplicate entries from this pos_product
        sort(pos_product_iter->begin(), pos_product_iter->end());
        vector<BinaryString_t>::iterator new_end = unique(pos_product_iter->begin(), pos_product_iter->end());
        pos_product_iter->resize(new_end - pos_product_iter->begin());

        // if this is the first iteration of pos_product, then take each individual sum term in the product's sum and separate them into individual products in the new_sum_of_products sequence
        if(old_sum_of_products.empty())
        {
            for(vector<BinaryString_t>::iterator pos_product_sum_iter = pos_product_iter->begin(); pos_product_sum_iter != pos_product_iter->end(); ++pos_product_sum_iter)
            {
                vector<BinaryString_t> new_sop_sum;
                new_sop_sum.push_back(*pos_product_sum_iter);
                new_sum_of_products.push_back(new_sop_sum);
                new_sop_sum.clear();
            }
        }
        else
        {
            // for each summed term in the factored term in product_of_sums
            for(vector<BinaryString_t>::iterator pos_product_sum_iter = pos_product_iter->begin(); pos_product_sum_iter != pos_product_iter->end(); ++pos_product_sum_iter)
            {
                // for each summed term (sequence of factored terms) in old_sum_of_products
                for(vector<vector<BinaryString_t> >::iterator old_sop_sum_iter = old_sum_of_products.begin(); old_sop_sum_iter != old_sum_of_products.end(); ++old_sop_sum_iter)
                {
                    // copy the old summed term as a new summed term
                    vector<BinaryString_t> new_sop_sum(*old_sop_sum_iter);

                    bool pos_sum_element_matches_sop_factor_element = false;

                    //! determine if the product_of_sums's product's sum's term is already present in our new_sum_of_products's sum's factors, if it is, then don't add it again (since X AND X = X, we might as well just store one X rather than two)
                    // for each factored term in the summed term in old_sum_of_products
                    for(vector<BinaryString_t>::iterator old_sop_sum_product_iter = old_sop_sum_iter->begin(); old_sop_sum_product_iter != old_sop_sum_iter->end(); ++old_sop_sum_product_iter)
                    {
                        if((*pos_product_sum_iter) == (*old_sop_sum_product_iter))
                        {
                            pos_sum_element_matches_sop_factor_element = true;
                            break;
                        }
                    }

                    // if there is not a duplicate, then add the pos-sum's element to the sop's factors
                    if(!pos_sum_element_matches_sop_factor_element)
                    {
                        new_sop_sum.push_back(*pos_product_sum_iter);
                        sort(new_sop_sum.begin(), new_sop_sum.end());
                    }

                    new_sum_of_products.push_back(new_sop_sum);
                }
            }
        }

        sort(new_sum_of_products.begin(), new_sum_of_products.end());
        old_sum_of_products.swap(new_sum_of_products);
        new_sum_of_products.clear();
    }

    return old_sum_of_products;
}

SetOfRowNumbers_t Remove_Dont_Cares(const SetOfRowNumbers_t &set_of_row_numbers, const TruthTableString_t &truth_table_string)
{
    SetOfRowNumbers_t function_result;

    for(SetOfRowNumbers_t::const_iterator iter = set_of_row_numbers.begin(); iter != set_of_row_numbers.end(); ++iter)
    {
        if('X' != truth_table_string.at(*iter))
        {
            function_result.insert(function_result.end(), *iter);
        }
    }

    return function_result;
}

SetOfRowNumbers_t Union_All_Implicant_Row_Number_Sets(const Implicants_t &implicants)
{
    return Union_Set_Subsets(Get_Set_Of_Map_Keys(implicants));
}

// std::ostream overloaded operators
ostream &operator<<(ostream &stream, const Implicants_t &implicants)
{
    for(Implicants_t::const_iterator implicant = implicants.begin(); implicant != implicants.end(); ++implicant)
    {
        stream << implicant->first << '\t' << implicant->second << '\n';
    }

    return stream;
}

ostream &operator<<(ostream &stream, const ImplicantsWithSameNumberOfOnes_t &implicant_groups)
{
    for(ImplicantsWithSameNumberOfOnes_t::const_iterator implicant_group = implicant_groups.begin(); implicant_group != implicant_groups.end(); ++implicant_group)
    {
        stream << "Number Of Ones: " << implicant_group->first << '\n' << implicant_group->second << '\n';
    }

    return stream;
}

ostream &operator<<(ostream &stream, const Minterms_t &minterms)
{
    for(Minterms_t::const_iterator minterm = minterms.begin(); minterm != minterms.end(); ++minterm)
    {
        stream << minterm->first << '\t' << minterm->second << '\n';
    }

    return stream;
}

ostream &operator<<(ostream &stream, const SetOfRowNumbers_t &set_of_row_numbers)
{
    stream << 'm';

    if(set_of_row_numbers.size() == 1)
    {
        stream << (*(set_of_row_numbers.begin()));
    }
    else
    {
        bool already_output_first_row = false;

        stream << '(';

        for(SetOfRowNumbers_t::const_iterator iter = set_of_row_numbers.begin(); iter != set_of_row_numbers.end(); ++iter)
        {
            if(already_output_first_row)
            {
                stream << ',';
            }
            else
            {
                already_output_first_row = true;
            }

            stream << (*iter);
        }

        stream << ')';
    }

    return stream;
}

Implicants_t Get_Optimal_Minterms(TruthTableString_t truth_table_string)
{
    cout << "Get_Optimal_Minterms('" << truth_table_string << "');" << endl;
    Implicants_t minterm_implicants = Quine_McCluskey(truth_table_string);

    return minterm_implicants;
}

Implicants_t Get_Optimal_Maxterms(TruthTableString_t truth_table_string)
{
    cout << "Get_Optimal_Maxterms('" << truth_table_string << "');" << endl;
    // invert the truth table row values
    for(string::iterator iter = truth_table_string.begin(); iter != truth_table_string.end(); ++iter)
    {
        if('1' == (*iter))
            (*iter) = '0';
        else if('0' == (*iter))
            (*iter) = '1';
    }

    Implicants_t maxterm_implicants = Quine_McCluskey(truth_table_string);

    for(Implicants_t::iterator maxterm_iter = maxterm_implicants.begin(); maxterm_iter != maxterm_implicants.end(); ++maxterm_iter)
    {
        for(unsigned int var_index = 0; var_index < maxterm_iter->second.length(); ++var_index)
        {
            if('X' != maxterm_iter->second[var_index])
            {
                if('0' == maxterm_iter->second[var_index])
                {
                    maxterm_iter->second[var_index] = '1';
                }
                else
                {
                    maxterm_iter->second[var_index] = '0';
                }
            }
        }
    }

    return maxterm_implicants;
}

string Get_SOP_Expression_String(Implicants_t minterms, vector<string> var_names)
{
    string sop_string;

    Implicants_t solution = minterms;

    cout << "SOP Solution" << endl << solution;

    if(solution.size() > 1) sop_string += '(';

    bool we_have_output_first_sum_product = false;

    for(Implicants_t::iterator minterm_iter = solution.begin(); minterm_iter != solution.end(); ++minterm_iter)
    {
        // do not put a + before the first element
        if(we_have_output_first_sum_product)
            sop_string += '+';
        else
            we_have_output_first_sum_product = true;

        bool we_have_output_first_product_factor = false;

        string term = minterm_iter->second;

        // count the number of fixed variables in the minterm; we only need to surround the minterm with parenthesis if there is more than two variables

        int vars_used = 0;
        for(unsigned int var_index = 0; var_index < term.length(); ++var_index)
        {
            if('X' != term[var_index]) ++vars_used;
        }

        if(vars_used > 1) sop_string += '(';

        for(unsigned int var_index = 0; var_index < term.length(); ++var_index)
        {
            if('X' != term[var_index])
            {
                if(we_have_output_first_product_factor)
                    sop_string += '*';
                else
                    we_have_output_first_product_factor = true;

                if('0' == term[var_index])
                {
                    sop_string += '~' + var_names[var_index];
                }
                else
                {
                    sop_string += var_names[var_index];
                }
            }
        }

        if(vars_used > 1) sop_string += ')';
    }

    if(solution.size() > 1) sop_string += ')';

    return sop_string;
}

string Get_POS_Expression_String(Implicants_t maxterms, vector<string> var_names)
{
    string pos_string;

    Implicants_t solution = maxterms;
    cout << "POS Solution" << endl << solution;

    if(solution.size() > 1) pos_string += '(';

    bool we_have_output_first_sum_product = false;

    for(Implicants_t::iterator maxterm_iter = solution.begin(); maxterm_iter != solution.end(); ++maxterm_iter)
    {
        // do not put a + before the first element
        if(we_have_output_first_sum_product)
            pos_string += '*';
        else
            we_have_output_first_sum_product = true;

        bool we_have_output_first_product_factor = false;

        string term = maxterm_iter->second;

        // count the number of fixed variables in the minterm; we only need to surround the minterm with parenthesis if there is more than two variables

        int vars_used = 0;
        for(unsigned int var_index = 0; var_index < term.length(); ++var_index)
        {
            if('X' != term[var_index]) ++vars_used;
        }

        if(vars_used > 1) pos_string += '(';

        for(unsigned int var_index = 0; var_index < term.length(); ++var_index)
        {
            if('X' != term[var_index])
            {
                if(we_have_output_first_product_factor)
                    pos_string += '+';
                else
                    we_have_output_first_product_factor = true;

                if('1' == term[var_index])
                {
                    pos_string += var_names[var_index];
                }
                else
                {
                    pos_string += '~' + var_names[var_index];
                }
            }
        }

        if(vars_used > 1) pos_string += ')';
    }

    if(solution.size() > 1) pos_string += ')';

    return pos_string;
}

