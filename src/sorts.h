#pragma once
#include<vector>
namespace sorts
{
    template <typename T >
    inline void quick_sort_private(std::vector<T> & vec, size_t start, size_t end)
    {
        T separator = vec[start + (end - start) / 2];
        size_t left_pointer  = start;
        size_t right_pointer = end - 1;

        do
        {
            while (vec[left_pointer] < separator)
            {
                left_pointer++;
            }

            while (vec[right_pointer] > separator)
            {
                right_pointer--;
            }

            if (left_pointer <= right_pointer)
            {
                std::swap(vec[left_pointer], vec[right_pointer]);
                left_pointer++;
                right_pointer--;
            }
        } while (left_pointer <= right_pointer);

        if (right_pointer > start)
        {
            quick_sort_private(vec, start, right_pointer + 1);
        }
        if (end > left_pointer)
        {
            quick_sort_private(vec, left_pointer, end);
        }
    }

    template <typename T>
    inline decltype(auto) quick_sort(std::vector<T> vec)
    {
        quick_sort_private(vec, 0, vec.size());
        return vec;
    }

    template <typename T>
    inline void merge_sort_private(std::vector<T> & vec, size_t start, size_t end)
    {
        if (end - start < 2)
        {
            return;
        }
        if (end - start == 2)
        {
            if (vec[start] > vec[start + 1])
            {
                std::swap(vec[start], vec[start + 1]);
            }
            return;
        }
        merge_sort_private(vec, start, start + (end - start) / 2);
        merge_sort_private(vec, start + (end - start) / 2, end);
        std::vector<T> temp;

        size_t startFirstOne = start;
        size_t endFirstOne = start + (end - start) / 2;
        size_t startSecondOne = endFirstOne;

        while (temp.size() < end - start)
        {
            if (startFirstOne >= endFirstOne ||
            (startSecondOne < end && vec[startSecondOne] <= vec[startFirstOne]))
            {
                temp.push_back(vec[startSecondOne++]);
            }
            else
            {
                temp.push_back(vec[startFirstOne++]);
            }
        }

        for (size_t i = start; i < end; i++)
        {
            vec[i] = temp[i - start];
        }
    }

    template <typename T>
    inline decltype(auto) merge_sort(std::vector<T> vec)
    {
        merge_sort_private(vec, 0, vec.size());
        return vec;
    }

    template <typename T>
    inline decltype(auto) bubble_sort(std::vector<T> vec)
    {
        for (int i = vec.size() - 1; i >= 1; i--)
        {
            for (int j = 0; j < i; j++)
            {
                if (vec[j] > vec[j + 1])
                    std::swap(vec[j], vec[j + 1]);
            }
        }
        return vec;
    }

    template< typename T>
    inline decltype(auto) insertion_sort(std::vector<T> vec)
    {
        for (int i = 1; i < vec.size(); i++)
        {
            T key = vec[i];
            int j = i - 1;
            while (j >= 0 && vec[j] > key)
            {
                vec[j + 1] = vec[j];
                j--;
            }
            vec[j + 1] = key;
        }
        return vec;
    }
}