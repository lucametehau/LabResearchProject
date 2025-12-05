with open('test.in', 'r') as file:
    lines = file.readlines()
    ind = 0
    seg = []
    while lines[ind] != '\n':
        line = lines[ind].strip().split('-')
        x, y = int(line[0]), int(line[1])
        seg.append((x, y))
        ind += 1

    ind += 1
    total_fresh = 0
    while ind < len(lines):
        x = int(lines[ind].strip())
        fresh = False
        for s in seg:
            if s[0] <= x <= s[1]:
                fresh = True
                break
        total_fresh += int(fresh)
        ind += 1

    seg.sort()

    l, r = 0, -1
    good_ids = 0
    for s in seg:
        if s[0] > r:
            good_ids += r - l + 1
            l, r = s[0], s[1]
        elif s[1] > r:
            r = s[1]
        print(l, r, good_ids)
    good_ids += r - l + 1
    print(total_fresh, good_ids)
