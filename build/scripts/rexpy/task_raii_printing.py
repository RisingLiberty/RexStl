import diagnostics

class TaskRaiiPrint(object):
  def __init__(self, msg):
    self._msg = msg
    self._finished_msg = "done"

    diagnostics.log_info(msg)
  
  def failed(self):
    self._finished_msg = "failed"

  def __del__(self):
    diagnostics.log_info(f"{self._msg} - {self._finished_msg}")