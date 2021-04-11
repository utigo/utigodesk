var utigodesk_addon = require('bindings')('utigodesk_addon.node')
var utigodesk_callback = require('bindings')('utigodesk_callback.node')

function u16str2ab(str) {
  var buf = new ArrayBuffer(str.length * 2)
  var bufView = new Uint16Array(buf)
  for (var i = 0, strLen = str.length; i < strLen; i++) {
    bufView[i] = str.charCodeAt(i)
  }
  return buf;
}

function u8str2ab(str) {
  var buf = new ArrayBuffer(str.length)
  var bufView = new Uint8Array(buf)
  for (var i = 0, strLen = str.length; i < strLen; i++) {
    bufView[i] = str.charCodeAt(i)
  }
  return buf
}

function ab2u16str(buf) {
  return String.fromCharCode.apply(null, new Uint16Array(buf));
}

function ab2u8str(buf) {
  return String.fromCharCode.apply(null, new Uint8Array(buf))
}

function callCppFunction(msg) {
  console.log('callCppFunction web msg:', msg)
  console.log('callCppFunction web msg type:', typeof msg)
  console.log('callCppFunction web msg size:', msg.length)
  console.log('callCppFunction C++ return:', utigodesk_addon.mainEntry(u16str2ab(msg)))
}

function status(msg) {
  console.log('JavaScript Recevie from C++:', ab2wstr(msg))
}

function callBackCpp(msg) {
  utigodesk_callback(status, msg)
}
