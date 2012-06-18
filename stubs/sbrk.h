// Increase program data space. As malloc and related functions depend on this, it is useful to have a working implementation. The following suffices for a standalone system; it exploits the symbol end automatically defined by the GNU linker.

caddr_t sbrk(int incr){
  extern char end;		/* Defined by the linker */
  static char *heap_end;
  char *prev_heap_end;
 
  if (heap_end == 0) {
    heap_end = &end;
  }
  prev_heap_end = heap_end;
  if (heap_end + incr > stack_ptr)
    {
      _write (1, "Heap and stack collision\n", 25);
      abort ();
    }

  heap_end += incr;
  return (caddr_t) prev_heap_end;
}
