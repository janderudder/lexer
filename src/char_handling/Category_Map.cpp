/**
 *  ~~ Toy programming language ~~
 *
 *  Category_Map class implementation.
 *
 *  Maps character values to corresponding lexical categories.
 *
 */
#include "char_handling/Category_Map.hpp"

/**
 *  Static member
 */
std::vector<Char_Category> Category_Map::m_cat_index_map;


/**
 *  Initialize mapping between chars and their category
 */
void Category_Map::init()
{
    m_cat_index_map.assign(255, Char_Category::OTHER);

    m_cat_index_map['\0'] = Char_Category::END_OF_FILE;

    for (auto i='0'; i < '9'; ++i) {
        m_cat_index_map[i] = Char_Category::NUMERIC;
    }

    for (auto i='a'; i < 'z'; ++i) {
        m_cat_index_map[i] = Char_Category::ALPHABETIC;
    }

    for (auto i='A'; i < 'Z'; ++i) {
        m_cat_index_map[i] = Char_Category::ALPHABETIC;
    }

    m_cat_index_map[' '] = Char_Category::DELIMITER;
    m_cat_index_map['\t'] = Char_Category::DELIMITER;
    m_cat_index_map['\n'] = Char_Category::DELIMITER;

    m_cat_index_map[','] = Char_Category::PUNCTUATION;
    m_cat_index_map[';'] = Char_Category::PUNCTUATION;
    m_cat_index_map[':'] = Char_Category::PUNCTUATION;

    m_cat_index_map['='] = Char_Category::OPERATOR;
    m_cat_index_map['+'] = Char_Category::OPERATOR;
    m_cat_index_map['-'] = Char_Category::OPERATOR;
    m_cat_index_map['*'] = Char_Category::OPERATOR;
    m_cat_index_map['/'] = Char_Category::OPERATOR;
    m_cat_index_map['&'] = Char_Category::OPERATOR;
    m_cat_index_map['?'] = Char_Category::OPERATOR;
    m_cat_index_map['!'] = Char_Category::OPERATOR;
    m_cat_index_map['|'] = Char_Category::OPERATOR;
    m_cat_index_map['^'] = Char_Category::OPERATOR;

}



bool Category_Map::is_init()
{
    return !m_cat_index_map.empty();
}



/**
 *  Access a category (instance's method)
 */
Char_Category Category_Map::operator[](const char value) const noexcept
{
    return m_cat_index_map[value];
}


/**
 *  Access a category (instance's method)
 */
Char_Category Category_Map::category_of(const char value) const noexcept
{
    return m_cat_index_map[value];
}
