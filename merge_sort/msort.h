#pragma once
class A {
    template<class RandomAccessIterator, class Compare>
    static void merge(RandomAccessIterator first,
               std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> &buffer,
               Compare comp,
               typename std::iterator_traits<RandomAccessIterator>::difference_type LeftOfFirst,
               typename std::iterator_traits<RandomAccessIterator>::difference_type RightOfFirst,
               typename std::iterator_traits<RandomAccessIterator>::difference_type LeftOfSecond,
               typename std::iterator_traits<RandomAccessIterator>::difference_type RightOfSecond) {
        typename std::iterator_traits<RandomAccessIterator>::difference_type idx{};
        while (LeftOfFirst <= RightOfFirst and LeftOfSecond <= RightOfSecond) {
            if (comp(*(first + LeftOfFirst), *(first + LeftOfSecond))) {
                buffer[idx++] = *(first + LeftOfFirst++);
            } else {
                buffer[idx++] = *(first + LeftOfSecond++);
            }
        }
        while (LeftOfFirst <= RightOfFirst) {
            buffer[idx++] = *(first + LeftOfFirst++);
        }
        while (LeftOfSecond <= RightOfSecond) {
            buffer[idx++] = *(first + LeftOfSecond++);
        }
    }

public:
    template<class RandomAccessIterator, class Compare>
    static std::enable_if_t<!std::is_same_v<typename std::iterator_traits<RandomAccessIterator>::iterator_category,
    std::random_access_iterator_tag>, void>
    msort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        std::cout << 123 << std::endl;
    }

    template<class RandomAccessIterator, class Compare>
    static std::enable_if_t<std::is_same_v<typename std::iterator_traits<RandomAccessIterator>::iterator_category,
    std::random_access_iterator_tag>, void>
    msort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
//    if constexpr(!std::is_same_v<typename std::iterator_traits<RandomAccessIterator>::iterator_category,
//        std::random_access_iterator_tag>){
//        std::cout << "sorted" << std::endl;
//    }
        typedef typename std::iterator_traits<RandomAccessIterator>::difference_type differenceType;
        typedef typename std::iterator_traits<RandomAccessIterator>::value_type valueType;

        differenceType n = last - first;
        differenceType len = 1;
        while (len < n) {
            differenceType i{};
            while (i < n) {

                differenceType LeftOfFirst = i;
                differenceType RightOfFirst = i + len - 1;
                differenceType LeftOfSecond = i + len;
                differenceType RightOfSecond = i + 2 * len - 1;

                if (LeftOfSecond >= n) {
                    break;
                }

                if (RightOfSecond >= n) {
                    RightOfSecond = n - 1;
                }

                std::vector<valueType> buffer(RightOfSecond - LeftOfFirst + 1); // buff
                A::merge(first, buffer, comp, LeftOfFirst, RightOfFirst, LeftOfSecond, RightOfSecond); // magic!

                for (differenceType j{}; j < RightOfSecond - LeftOfFirst + 1; ++j) {
                    *(first + i + j) = buffer[j];
                }

                i = i + 2 * len;
            }
            len = len * 2;
        }
    }
};
//template <class RandomAccessIterator, class Compare>
//void msort (RandomAccessIterator first, RandomAccessIterator last, Compare comp){
//    std :: cout << "Sorted" << std :: endl;
//}



