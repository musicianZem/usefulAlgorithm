#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

// 고정 값
const float ROBOT_WHEEL_DISTANCE = 0.1320f; // 양 바퀴 사이 거리(m)
const float ROBOT_WHEEL_RADIUS   = 0.0628f; // 바퀴 반지름
const float ENCODER_PER_1_CYCLE  = 6000.f;  // 바퀴가 한 바퀴 돌 때, 증가하는 Encoder 값
const float ROBOT_MOVE_PER_TICK  = 2 * M_PI * ROBOT_WHEEL_RADIUS / ENCODER_PER_1_CYCLE; // 바퀴 인코더 값 1당 움직이는 거리

// 로봇 시작 위치
float lx = 0.f - (ROBOT_WHEEL_DISTANCE/2.f);
float ly = 0.f;
float rx = 0.f + (ROBOT_WHEEL_DISTANCE/2.f);
float ry = 0.f;
float theta = 0.f; // 로봇이 바라보고 있는 각도


void getNextPointSameWheelSpeed(int enc) {
    // 실제 움직인 호의 길이 계산
    float moveDist = enc * ROBOT_MOVE_PER_TICK; // lenc or renc

    // 다음 좌표 계산
    lx += moveDist * cosf(theta + (M_PI/2.f));
    ly += moveDist * sinf(theta + (M_PI/2.f));
    rx += moveDist * cosf(theta + (M_PI/2.f));
    ry += moveDist * sinf(theta + (M_PI/2.f));
}

void getNextPointDiffSign(int lenc, int renc) {
    int absl = abs(lenc);
    int absr = abs(renc);

    // 실제 움직인 호의 길이 계산
    float moveL = absl * ROBOT_MOVE_PER_TICK;
    float moveR = absr * ROBOT_MOVE_PER_TICK;

    // 두 바퀴가 그린 호는 같은 중점 (ox, oy)를 원점으로 한다.
    // 이를 내분점으로 구한다.
    float ox = (moveL*rx + moveR*lx) / (moveL + moveR);
    float oy = (moveL*ry + moveR*ly) / (moveL + moveR);

    // 원점에서 각 바퀴까지의 거리를 계산한다.
    float lx_dist = ox-lx, ly_dist = oy-ly;
    float ldist = sqrt(lx_dist*lx_dist + ly_dist*ly_dist);
    float rx_dist = ox-rx, ry_dist = oy-ry;
    float rdist = sqrt(rx_dist*rx_dist + ry_dist*ry_dist);

    // 각 lenc, renc만큼 움직였을 때, 변화하는 각도값 dtheta를 계산한다.
    float dtheta;
    if( absl > absr ) { 
        dtheta = moveL / (ldist);
    } else {
        dtheta = moveR / (rdist);
    }

    if( lenc > 0 ) {
        dtheta = -dtheta;
    }

    // 기존 각도에 해당 값을 더해준다.
    theta += dtheta;

    // 다음 좌표 계산
    lx = ox + ldist * cosf(M_PI + theta);
    ly = oy + ldist * sinf(M_PI + theta);
    rx = ox + rdist * cosf(theta);
    ry = oy + rdist * sinf(theta);
}

void getNextPointSameSign(int lenc, int renc) {
    // 실제 움직인 호의 길이 계산
    float moveL = lenc * ROBOT_MOVE_PER_TICK;
    float moveR = renc * ROBOT_MOVE_PER_TICK;

    // 두 바퀴가 그린 호는 같은 중점 (ox, oy)를 원점으로 한다.
    // 이를 외분점으로 구한다.
    float ox = (moveL*rx - moveR*lx) / (moveL - moveR);
    float oy = (moveL*ry - moveR*ly) / (moveL - moveR);

    // 원점에서 각 바퀴까지의 거리를 계산한다.
    float lx_dist = ox-lx, ly_dist = oy-ly;
    float ldist = sqrt(lx_dist*lx_dist + ly_dist*ly_dist);
    float rx_dist = ox-rx, ry_dist = oy-ry;
    float rdist = sqrt(rx_dist*rx_dist + ry_dist*ry_dist);

    // 각 l, r만큼 움직였을 때, 변화하는 각도값 dtheta를 계산한다.
    float dtheta;
    if( lenc != 0 ) { 
        dtheta = moveL / (ldist);
    } else {
        dtheta = moveR / (rdist);
    }

    // 기존 각도에 해당 값을 더해준다.
    theta += dtheta;

    // 다음 좌표 lx, ly, rx, ry를 원점 ox, oy로부터 xdist만큼 떨어져있는 theta 각도에 표기한다.
    if( fabsf(moveL) < fabsf(moveR) ) {
        lx = ox + ldist * cosf(theta);
        ly = oy + ldist * sinf(theta);
        rx = ox + rdist * cosf(theta);
        ry = oy + rdist * sinf(theta);
    } else {
        lx = ox + ldist * cosf(M_PI - theta);
        ly = oy + ldist * sinf(M_PI - theta);
        rx = ox + rdist * cosf(M_PI - theta);
        ry = oy + rdist * sinf(M_PI - theta);
    }
}

int main() {

    cout << "시작 좌표" << endl;
    cout << lx << " " << ly << "       " << rx << " " << ry << endl;

    while( true ) {
        int l, r; cin >> l >> r;

        // 두 바퀴의 인코더 값이 같은 경우
        if( l == r ) {
            getNextPointSameWheelSpeed(l);
        }
        // 두 바퀴의 인코더 부호가 다른 경우
        else if( l*r < 0 ) {
            getNextPointDiffSign(l, r);
        }
        // 두 바퀴의 인코더 부호는 같으나, 값이 다른 경우
        else {
            getNextPointSameSign(l, r);
        }

        cout << lx << " " << ly << "       " << rx << " " << ry << endl;
    }
}
