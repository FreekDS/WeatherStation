// Enforces a check that verifies whether a method exists on a CRTP base class
// Use this in a contexpr ctor of the base class.
// Note that the static assert is never hit in case of non-existing MethodName on DerivedClass! Instead an compiler error is given.
// The check must be placed in the (constexpr) ctor of the base class to ensure it is evaluated (templates are lazy evaluated)
#define CRTP_REQUIRED(DerivedClass, MethodName, ReturnType) \
    static_assert(sizeof(&DerivedClass::MethodName) > 0, \
    "CRTP requirement failed: " #DerivedClass " must implement '" #ReturnType " " #MethodName "(...)'!");
