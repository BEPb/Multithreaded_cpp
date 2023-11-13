#include <vector>
#include <string>
#include <fstream>

void read_dataset(std::vector<uint32_t> &dataset) {
    std::string filename = "dataset_12656_4.txt";
    std::ifstream in(filename);
    uint32_t val;

    while (in >> val) {
        dataset.push_back(val);
    }

    in.close();
}

void save_dataset(const std::vector<uint32_t> &dataset) {
    std::string filename = "sorted.txt";
    std::ofstream out(filename);

    for (const uint32_t &val : dataset) {
        out << val << " ";
    }
}

void merge_sort(std::vector<uint32_t>::iterator left, std::vector<uint32_t>::iterator right)
{
#pragma omp parallel
    {
        #pragma omp single nowait
        size_t count = std::distance(left, right);
        if (count <= 1)
            return;
        std::vector<uint32_t>::iterator middle = left;
        std::advance(middle, count / 2);

        #pragma omp task
        {
        merge_sort(left, middle);
        }

        #pragma omp task
        {
        merge_sort(middle, right);
        }

        #pragma omp taskwait
        std::vector<uint32_t> temp(count);
        std::vector<uint32_t>::iterator from_left = left;
        std::vector<uint32_t>::iterator from_right = middle;
        size_t temp_idx = 0;

        while (from_left != middle && from_right != right) {
            if (*from_left < *from_right) {
                temp[temp_idx] = *from_left;
                ++from_left;
            }
            else {
                temp[temp_idx] = *from_right;
                ++from_right;
            }

            ++temp_idx;
        }

        if (from_left != middle) {
            std::copy(from_left, middle, &temp[temp_idx]);
        }

        if (from_right != right) {
            std::copy(from_right, right, &temp[temp_idx]);
        }

        std::copy(temp.begin(), temp.end(), left);
    }
}

int main() {
    std::vector<uint32_t> dataset;
    read_dataset(dataset);

    merge_sort(dataset.begin(), dataset.end());

    save_dataset(dataset);

    return 0;
}