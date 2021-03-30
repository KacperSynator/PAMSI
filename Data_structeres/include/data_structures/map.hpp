#ifndef MAP_HPP_
#define MAP_HPP_



int hash(const std::string& str)
{
    int result = 0;
    for(int i=0; i< str.length() ;i++)
    {
        result += static_cast<int> ((i+1)*str[i]);
    }
    return result % 1000;
}

template <typename KeyType, typename ValueType>
class Map
{
public:
  Map() {}
  Map(const Map& otherMap) {this->tab=otherMap->tab;  }

  void insert(const KeyType& key ,const ValueType& value);
  ValueType& operator[](const KeyType& key);
  void remove(const KeyType& key);

private:
  std::array<ValueType, 1000 > tab;
};


template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
  auto index = hash(key);
  tab[index]=value;
}

template <typename KeyType, typename ValueType>
ValueType &Map<KeyType, ValueType>::operator[](const KeyType &key) {

  auto index =hash(key);
  return tab[index];

}

template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::remove(const KeyType &key)
    {
        auto index = hash(key);
        tab[index]=0;
    }

#endif /* MAP_HPP_ */
