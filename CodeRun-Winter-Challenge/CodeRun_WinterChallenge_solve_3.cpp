#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <map>
#include <set>
#include <random>
#include <cmath>

using namespace std;
using ll = long long;
using ld = long double;

int main() {

    vector<ll> nums;

    nums.push_back(897612484786617600LL);
    nums.push_back(748010403988848000LL);
    nums.push_back(673209363589963200LL);
    nums.push_back(448806242393308800LL);
    nums.push_back(374005201994424000LL);
    nums.push_back(299204161595539200LL);
    nums.push_back(224403121196654400LL);
    nums.push_back(149602080797769600LL);
    nums.push_back(112201560598327200LL);
    nums.push_back(106858629141264000LL);
    nums.push_back(74801040398884800LL);
    nums.push_back(72779390658374400LL);
    nums.push_back(60649492215312000LL);
    nums.push_back(48519593772249600LL);
    nums.push_back(36389695329187200LL);
    nums.push_back(30324746107656000LL);
    nums.push_back(24259796886124800LL);
    nums.push_back(20216497405104000LL);
    nums.push_back(18194847664593600LL);
    nums.push_back(12129898443062400LL);
    nums.push_back(10108248702552000LL);
    nums.push_back(8086598962041600LL);
    nums.push_back(6064949221531200LL);
    nums.push_back(4043299481020800LL);
    nums.push_back(3032474610765600LL);
    nums.push_back(2888071057872000LL);
    nums.push_back(2021649740510400LL);
    nums.push_back(1732842634723200LL);
    nums.push_back(1516237305382800LL);
    nums.push_back(1444035528936000LL);
    nums.push_back(1010824870255200LL);
    nums.push_back(866421317361600LL);
    nums.push_back(782574093100800LL);
    nums.push_back(577614211574400LL);
    nums.push_back(391287046550400LL);
    nums.push_back(288807105787200LL);
    nums.push_back(260858031033600LL);
    nums.push_back(195643523275200LL);
    nums.push_back(130429015516800LL);
    nums.push_back(97821761637600LL);
    nums.push_back(93163582512000LL);
    nums.push_back(65214507758400LL);
    nums.push_back(55898149507200LL);
    nums.push_back(48910880818800LL);
    nums.push_back(46581791256000LL);
    nums.push_back(32607253879200LL);
    nums.push_back(27949074753600LL);
    nums.push_back(26985313555200LL);
    nums.push_back(18632716502400LL);
    nums.push_back(13492656777600LL);
    nums.push_back(9316358251200LL);
    nums.push_back(8995104518400LL);
    nums.push_back(6746328388800LL);
    nums.push_back(4497552259200LL);
    nums.push_back(3373164194400LL);
    nums.push_back(3212537328000LL);
    nums.push_back(2248776129600LL);
    nums.push_back(1927522396800LL);
    nums.push_back(1686582097200LL);
    nums.push_back(1606268664000LL);
    nums.push_back(1124388064800LL);
    nums.push_back(963761198400LL);
    nums.push_back(642507465600LL);
    nums.push_back(481880599200LL);
    nums.push_back(321253732800LL);
    nums.push_back(293318625600LL);
    nums.push_back(240940299600LL);
    nums.push_back(160626866400LL);
    nums.push_back(146659312800LL);
    nums.push_back(128501493120LL);
    nums.push_back(97772875200LL);
    nums.push_back(80313433200LL);
    nums.push_back(73329656400LL);
    nums.push_back(64250746560LL);
    nums.push_back(48886437600LL);
    nums.push_back(41902660800LL);
    nums.push_back(27935107200LL);
    nums.push_back(20951330400LL);
    nums.push_back(13967553600LL);
    nums.push_back(10475665200LL);
    nums.push_back(6983776800LL);
    nums.push_back(5587021440LL);
    nums.push_back(4655851200LL);
    nums.push_back(3491888400LL);
    nums.push_back(2793510720LL);
    nums.push_back(2327925600LL);
    nums.push_back(2205403200LL);
    nums.push_back(2095133040LL);
    nums.push_back(1396755360LL);
    nums.push_back(1102701600LL);
    nums.push_back(735134400LL);
    nums.push_back(698377680LL);
    nums.push_back(551350800LL);
    nums.push_back(367567200LL);
    nums.push_back(294053760LL);
    nums.push_back(245044800LL);
    nums.push_back(183783600LL);
    nums.push_back(147026880LL);
    nums.push_back(122522400LL);
    nums.push_back(110270160LL);
    nums.push_back(73513440LL);
    nums.push_back(61261200LL);
    nums.push_back(43243200LL);
    nums.push_back(36756720LL);
    nums.push_back(32432400LL);
    nums.push_back(21621600LL);
    nums.push_back(17297280LL);
    nums.push_back(14414400LL);
    nums.push_back(10810800LL);
    nums.push_back(8648640LL);
    nums.push_back(7207200LL);
    nums.push_back(6486480LL);
    nums.push_back(4324320LL);
    nums.push_back(3603600LL);
    nums.push_back(2882880LL);
    nums.push_back(2162160LL);
    nums.push_back(1441440LL);
    nums.push_back(1081080LL);
    nums.push_back(720720LL);
    nums.push_back(665280LL);
    nums.push_back(554400LL);
    nums.push_back(498960LL);
    nums.push_back(332640LL);
    nums.push_back(277200LL);
    nums.push_back(221760LL);
    nums.push_back(166320LL);
    nums.push_back(110880LL);
    nums.push_back(83160LL);
    nums.push_back(55440LL);
    nums.push_back(50400LL);
    nums.push_back(45360LL);
    nums.push_back(27720LL);
    nums.push_back(25200LL);
    nums.push_back(20160LL);
    nums.push_back(15120LL);
    nums.push_back(10080LL);
    nums.push_back(7560LL);
    nums.push_back(5040LL);
    nums.push_back(2520LL);
    nums.push_back(1680LL);
    nums.push_back(1260LL);
    nums.push_back(840LL);
    nums.push_back(720LL);
    nums.push_back(360LL);
    nums.push_back(240LL);
    nums.push_back(180LL);
    nums.push_back(120LL);
    nums.push_back(60LL);
    nums.push_back(48LL);
    nums.push_back(36LL);
    nums.push_back(24LL);
    nums.push_back(12LL);
    nums.push_back(6LL);
    nums.push_back(4LL);
    nums.push_back(2LL);
    nums.push_back(1LL);

    int n;
    cin >> n;
    while(n--) {
        ll l, r;
        cin >> l >> r;

        int cnt = 0;
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] >= l && nums[i] <= r) {
                cnt++;
            }
        }

        cout << cnt << "\n";
    }

    return 0;
}
