# Access Violation Analysis
- Exception: 0xC0000005 Access violation reading location 0x0000000000000000
- Thread: 30432
- Function: ma_device_stop
- Callstack: [ma_device_stop, ma_wfopen, kernel32.dll!00007ff9dd65dda7, ntdll.dll!00007ff9de879c5c]
- Next steps: Find definitions of ma_device_stop and ma_wfopen, inspect their implementations, and evaluate expressions around the access violation.