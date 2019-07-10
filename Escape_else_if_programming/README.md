# [if else] to [Scheduler]

| TIME TABLE |    DO WHAT   |
|:----------:|:------------:|
|   1000ms   | GO FORWARD   |
|   3000ms   | TURN LEFT    |
|   2000ms   | GO BACKWARD  |

# if - else if version

```c++

static int timer = 0;
if( timer < 1000 )
    goForward();
else if( timer < 4000 )
    turnLeft(); // 1000 + 3000
else if( timer < 6000 )
    goBackward(); // 1000 + 3000 + 2000
else
    return 0;

```

# scheduler version

```c++

scheduler.push( 1000, goForward() );
scheduler.push( 3000, turnLeft() );
scheduler.push( 2000, goBackward() );

while( !scheduler.empty() )
    scheduler.run();

```
