import sys, signal, commands

DEFAULT_TIMEOUT = 5

class TimeoutException(Exception):
    """A timeout has occurred."""
    pass

def timeout(timeout):
    """This decorator takes a timeout parameter in seconds."""
    def wrap_function(function):
        def wrapped(self, *args):
            def handler(signum, frame):
                raise TimeoutException()
            # get the old SIGALRM handler
            old = signal.signal(signal.SIGALRM, handler) 
            # set the alarm
            signal.alarm(timeout) 
            try:
                result = function(self, *args)
            except TimeoutException:
                self.assertTrue(False, function.__name__ + " timed out.")
            except:
                raise
            finally:
                # restore existing SIGALRM handler
                signal.signal(signal.SIGALRM, old)
            signal.alarm(0)
            return result
        return wrapped
    return wrap_function
