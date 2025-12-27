
A real-time transaction ingestion and feature extraction pipeline in C++ with stateful sliding windows and bounded queues.



High=Level Architecture

Ingress (ISO8583 / JSON) 
   ↓
Normalization Layer
   ↓
Feature Engineering Engine
   ↓
Rule Engine
   ↓
ML Scoring Engine
   ↓
Decision Engine
   ↓
Audit & Explainability
