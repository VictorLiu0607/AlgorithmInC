# 一次归并
def merge(array, low, mid, high):
    """
    两段需要归并的序列从左往右遍历，逐一比较，小的就放到
    tmp里去，再取，再比，再放。
    """
    tmp = []
    i = low
    j = mid + 1
    while i <= mid and j <= high:
        if array[i] <= array[j]:
            tmp.append(array[i])
            i += 1
        else:
            tmp.append(array[j])
            j += 1
    while i <= mid:
        tmp.append(array[i])
        i += 1
    while j <= high:
        tmp.append(array[j])
        j += 1
    array[low:high + 1] = tmp


def merge_sort(array, low, high):
    if low < high:
        mid = (low + high) // 2
        merge_sort(array, low, mid)
        merge_sort(array, mid + 1, high)
        merge(array, low, mid, high)
    return array


def radix_sort(array):
    """基数排序"""
    i = 0  # 记录当前正在排拿一位，最低位为1
    max_num = max(array)  # 最大值
    j = len(str(max_num))  # 记录最大值的位数
    while i < j:
        bucket_list = [[] for _ in range(10)]  # 初始化桶数组
        for x in array:
            bucket_list[int(x / (10 ** i)) % 10].append(x)  # 找到位置放入桶数组
        # print(bucket_list)
        array.clear()
        for x in bucket_list:  # 放回原序列
            for y in x:
                array.append(y)
        i += 1
    return array


def redix_sort2(array):
    # 基数排序
    i = 0
    max_num = max(array)
    j = len(str(max_num))
    while i < j:
        bucket_list = [[] for _ in range(10)]
        for num in array:
            bucket_list[int(num / (10 ** i)) % 10].append(num)
        array.clear()
        for num_group in bucket_list:
            for num_new in num_group:
                array.append(num_new)
        i += 1
    return array


def insert_sort(array):
    # 循环的是第二个到最后（待摸的牌）
    for i in range(1, len(array)):
        # 待插入的数（摸上来的牌）
        min = array[i]
        # 已排好序的最右边一个元素（手里的牌的最右边）
        j = i - 1
        # 一只和排好的牌比较，排好的牌的牌的索引必须大于等于0
        # 比较过程中，如果手里的比摸上来的大，
        while j >= 0 and array[j] > min:
            # 那么手里的牌往右边移动一位，就是把j付给j+1
            array[j + 1] = array[j]
            # 换完以后在和下一张比较
            j -= 1
        # 找到了手里的牌比摸上来的牌小或等于的时候，就把摸上来的放到它右边
        array[j + 1] = min


def select_sort(array):
    for i in range(len(array) - 1):
        min = i
        for j in range(i + 1, len(array)):
            if array[j] < array[min]:
                min = j
        array[i], array[min] = array[min], array[i]
    return array


def shell_sort(li):
    """希尔排序"""
    gap = len(li) // 2
    while gap > 0:
        for i in range(gap, len(li)):
            tmp = li[i]
            j = i - gap
            while j >= 0 and tmp < li[j]:
                li[j + gap] = li[j]
                j -= gap
            li[j + gap] = tmp
        gap //= 2


def quick_sort(array, left, right):
    if left < right:
        mid = partition(array, left, right)
        quick_sort(array, left, mid - 1)
        quick_sort(array, mid + 1, right)
    return array


def partition(array, left, right):
    tmp = array[left]
    while left < right:
        while left < right and array[right] >= tmp:
            right -= 1
        array[left] = array[right]
        while left < right and array[left] <= tmp:
            left += 1
        array[right] = array[left]
    array[left] = tmp
    return left


def sift(array, left, right):
    """调整"""
    i = left  # 当前调整的小堆的父节点
    j = 2 * i + 1  # i的左孩子
    tmp = array[i]  # 当前调整的堆的根节点
    while j <= right:  # 如果孩子还在堆的边界内
        if j < right and array[j] < array[j + 1]:  # 如果i有右孩子,且右孩子比左孩子大
            j = j + 1  # 大孩子就是右孩子
        if tmp < array[j]:  # 比较根节点和大孩子，如果根节点比大孩子小
            array[i] = array[j]  # 大孩子上位
            i = j  # 新调整的小堆的父节点
            j = 2 * i + 1  # 新调整的小堆中I的左孩子
        else:  # 否则就是父节点比大孩子大，则终止循环
            break
    array[i] = tmp  # 最后i的位置由于是之前大孩子上位了，是空的，而这个位置是根节点的正确位置。


def heap(array):
    n = len(array)
    # 建堆，从最后一个有孩子的父亲开始，直到根节点
    for i in range(n // 2 - 1, -1, -1):
        # 每次调整i到结尾
        sift(array, i, n - 1)
    # 挨个出数
    for i in range(n - 1, -1, -1):
        # 把根节点和调整的堆的最后一个元素交换
        array[0], array[i] = array[i], array[0]
        # 再调整，从0到i-1
        sift(array, 0, i - 1)
    return array
