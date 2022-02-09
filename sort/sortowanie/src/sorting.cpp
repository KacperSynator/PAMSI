#include "sorting/sorting.hpp"

void bubbleSort(std::vector<int>& tab)
{
    for(unsigned long n=tab.size();n>0;n--)
        for(unsigned long i=0;i+1<n;i++)
        {
            if(tab[i+1]<=tab[i])
                std::swap(tab[i+1],tab[i]);
        }
}


void heapSort(std::vector<int>& tab)
{
    //heap construction
    for(unsigned long i = 1;i<tab.size();i++)
    {
        unsigned long k=i;
        while(k>0  && tab[(k-1)/2]<tab[k] )
        {
            std::swap(tab[k],tab[(k-1)/2]);
            k=(k-1)/2;
        }
    }

    //heap deconstruction
    for(unsigned long i = tab.size()-1;i>=1;i--)
    {
        std::swap(tab[i],tab[0]);
        unsigned long k=1,l=0,m;
        while(k<i)
        {
            if(k+1<i && tab[k+1]>tab[k])
                m=k+1;
            else
                m=k;

            if(tab[m]<=tab[l]) break;
            std::swap(tab[l],tab[m]);
            l=m; k=2*l+1;
        }
    }

}

void _quickSort(std::vector<int>& tab, unsigned long start, unsigned long end)
{
    if(end <= start || start < 0 || end >= tab.size())
        return;

    unsigned long pivot_index = end; // chose pivot as last element
    for(unsigned long i=start; i < pivot_index;)
    {
        if(tab[i] > tab[pivot_index])
        {
            std::swap(tab[pivot_index], tab[i]);
            std::swap(tab[i], tab[pivot_index - 1]);
            pivot_index--;
        }
        else
            i++;
    }
    _quickSort(tab, start, pivot_index - 1);
    _quickSort(tab, pivot_index + 1, end);
}
void quickSort(std::vector<int>& tab)
{
    _quickSort(tab, 0, tab.size()-1);
}




void mergeSort(std::vector<int>& tab)
{
    if(tab.size()<=1) return;

    unsigned long mid = tab.size()/2;
    std::vector<int> tab_left(tab.begin(),tab.begin()+mid);
    std::vector<int> tab_right(tab.begin()+mid,tab.end());
    mergeSort(tab_left);
    mergeSort(tab_right);

    unsigned long l=0,r=0,k=0;
    while(l<tab_left.size() && r<tab_right.size())
        if(tab_left[l] <= tab_right[r])
            tab[k++]=tab_left[l++];
        else
            tab[k++]=tab_right[r++];

    while(l<tab_left.size())
        tab[k++]=tab_left[l++];
    while(r<tab_right.size())
        tab[k++]=tab_right[r++];

}

