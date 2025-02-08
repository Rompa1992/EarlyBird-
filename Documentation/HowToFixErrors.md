# Error Fix Documentation

## Error Message  
[Copy and paste the exact error message]  

## Cause  
[Brief explanation of what caused the error]  

## Solution  
[Detailed steps or code changes that fixed the error]  

---
---

## Error Message  
__error C2065: 'Application': undeclared identifier__

## Cause  
- No namespace Idet 

## Solution  
prefix with eb::  

---
---

## Error Message  
declaration is incompatible with <error type>

## Cause  
missing include 

## Solution  
make sure to check includes. for this I was missing Core.h, which has the weak_ptr

---
---

## Error Message  
pointer or reference to incomplete type "eb::Actor" is not allowed
pointer or reference to incomplete type is not allowed

## Cause  
include

## Solution  
check include for type that pointer or reference is.
