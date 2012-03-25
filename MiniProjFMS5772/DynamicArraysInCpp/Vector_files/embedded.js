(function(w) {
  if (w._pg_print) return;
  w._pg_print = w.print;

  w._pg_loaded = false;
  w._pg_load = function() {
    if (w._pg_loaded) {
      if (w._p_g && w._p_g.$) return w._p_g.show();
      return;
    }
    w._pg_loaded = true;
    var p = document.createElement('script'); p.type = 'text/javascript'; p.async = true;
    p.src = '//cdn.printitgreen.com/js/printitgreen.js';
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(p, s);
  }

  w.print = function() {
    w._pg_print();
    w._pg_load();
  }
  
  if (w.addEventListener) {
    w.addEventListener('beforeprint', w._pg_load, false);
  } else if (w.attachEvent) {
    w.attachEvent('onbeforeprint', w._pg_load);
  }

})(window);
