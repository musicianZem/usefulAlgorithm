### vim에서 개행문자 ^M 제거하기

Windows에서 파일을 읽었을 때 가끔 나타나는 현상입니다.

**화면에 ^M 문자 출력하기**

```
:set ffs=unix
:e
```

파일 내부 ^M 한번에 삭제하기
```
:%s/^M//
```

**^M**은 직접 두 문자를 타이핑하는게 아니라 `Ctrl + v + m`을 입력하면 된다.
