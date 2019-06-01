/**
 *  ~~ Toy programming language ~~
 *
 *  Category_Map class,
 *  Char_Category enum.
 *
 *  Maps character values to corresponding lexical categories.
 *
 */
#pragma once
#include <vector>


enum Char_Category
{
    ALPHABETIC,     // includes underscore
    NUMERIC,
    OPERATOR,
    PUNCTUATION,
    DELIMITER,
    END_OF_FILE,
    OTHER,
    CAT_COUNT
};


/**
 *  Mapping Char_Category to a char value
 *  via the index of the array.
 */
class Category_Map
{
    static std::vector<Char_Category>  m_cat_index_map;

public:
    static void init();
    static bool is_init();

    Char_Category operator[](const char) const noexcept;
    Char_Category category_of(const char) const noexcept;

};
