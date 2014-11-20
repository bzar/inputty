.pragma library

function filter(coll, p) {
  var result = [];
  for(var i = 0; i < coll.length; ++i) {
    if(p(coll[i])) {
      result.push(coll[i]);
    }
  }
  return result;
}
function map(coll, fn) {
  var result = [];
  for(var i = 0; i < coll.length; ++i) {
    result.push(fn(coll[i]));
  }
  return result;
}
function contains(coll, el) {
  for(var i = 0; i < coll.length; ++i) {
    if(coll[i] === el) {
      return true;
    }
  }
  return false;
}
