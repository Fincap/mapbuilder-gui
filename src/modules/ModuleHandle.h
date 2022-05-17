#pragma once

/*
Interface for displaying module handles. Derived classes are responsible for
constructing and maintaining the references to the wrapped module, as well as
constructing a valid UI based on CollapsingHeader sections.
*/
class ModuleHandle
{
public:
  // Return Handle's alive status. If false, then Wrapper should delete.
  virtual bool showHandle() = 0;  // Must be implemented by derived.

protected:
  bool _alive;    // Determines if the Module should be deleted.
};
