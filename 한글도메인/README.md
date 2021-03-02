# npm express 한글도메인

평소 나는 아래와 같이 도메인 관리를 했었다.
```node.js
// app.js
var testRouter = require('./routes/test');

app.use('/test', testRouter);

// routes/test.js

var express = require('express');
var router = express.Router();

// domain.com/test
router.get('/', function(req, res, next) {
  res.render('test/index');
});

// domain.com/test/abcd
router.get('/abcd', function(req, res, next) {
  res.render('test/abcd');
});

module.exports = router;

```  

허나, 아래와 같이 경로를 한글로 만들수도 있더라.

```node.js

app.use(`/${encodeURI("한글도메인")`, koreanRouter);

```

