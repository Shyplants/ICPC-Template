struct point {ll x, y;};
struct line {point s, e;};
int ccw(point &p1, point &p2, point &p3) {
    ll tmp = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y;
    tmp -= p1.y * p2.x + p2.y * p3.x + p3.y * p1.x;
    return (0 < tmp) - (tmp < 0);
}
bool intersect(line &l1, line &l2) {
    int ccw1 = ccw(l1.s, l1.e, l2.s) * ccw(l1.s, l1.e, l2.e);
    int ccw2 = ccw(l2.s, l2.e, l1.s) * ccw(l2.s, l2.e, l1.e);
    return (ccw1 < 0) && (ccw2 < 0);
}