var events = require('events');
var util = require('util');
var a = function () {
    // events.EventEmitter.call(this);
};
util.inherits(a, events.EventEmitter);
console.log(a, new a())

// events.EventEmitter.call(this);ע��֮ǰ������
// F:\study\node\code>node events_study.js
// [Function: a] a {
  // _events: [Object: null prototype] {},
  // _eventsCount: 0,
  // _maxListeners: undefined
// }

// events.EventEmitter.call(this);ע��֮��������
// [Function: a] a {}