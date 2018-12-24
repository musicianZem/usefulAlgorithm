# 특정 조건만큼 수행해야 하는 코드를 우아하게 바꾼다.

| TIME TABLE | DO WHAT |
|:----------:|:-------:|
|   1000ms   |   전진  |
|   3000ms   | 좌 회전 |
|   2000ms   |   후진  |

# if - else if version

```c++

static int timer = 0;
if( timer < 1000 )
    전진();
else if( timer < 4000 )
    좌회전(); // 1000 + 3000
else if( timer < 6000 )
    후진(); // 1000 + 3000 + 2000
else
    return 0;

```

# scheduler version

```c++

scheduler.push( 1000, 전진() );
scheduler.push( 3000, 좌회전() );
scheduler.push( 2000, 후진() );

while( !scheduler.empty() )
    scheduler.run();

```
