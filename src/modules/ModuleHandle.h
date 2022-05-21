#pragma once
#include <memory>

/*
Interface for displaying module handles. Derived classes are responsible for
constructing and maintaining the references to the wrapped module, as well as
constructing a valid UI based on CollapsingHeader sections.
*/
class ModuleHandle
{
public:
  using Ptr = std::shared_ptr<ModuleHandle>;

  // Return Handle's alive status. If false, then Wrapper should delete.
  // int parameter is a number representing the order which the related
  // Module is executed in the Pipeline.
  virtual bool showHandle(int) = 0;  // Must be implemented by derived.

protected:
  bool alive_;    // Determines if the Module should be deleted.
};
