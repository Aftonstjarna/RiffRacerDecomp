// Histogram buckets describe successively doubled array capacities.
// Returns the occupied entries belonging to the selected capacity.
int __fastcall choose_array_capacity(const int* buckets, int* total)
{
    int occupied = 0;
    int selectedEntries = 0;
    int selectedCapacity = 0;
    int capacity = 1;
    for (; capacity / 2 < *total; capacity *= 2, ++buckets) {
        if (*buckets > 0) {
            occupied += *buckets;
            if (occupied > capacity / 2) {
                selectedCapacity = capacity;
                selectedEntries = occupied;
            }
        }
        if (occupied == *total)
            break;
    }
    *total = selectedCapacity;
    return selectedEntries;
}
