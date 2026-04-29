# DevOps

[TOC]



![how_company_ship_code_to_production](res/how_company_ship_code_to_production.png)

## DevOps

### KPI

Here are three key DevOps KPIs:

1. Deployment Frequency (DF)
2. Mean Time to Recovery (MTTR)
3. Change Failure Rate (CFR)

### Infrastructure as Code(IaC)

![infrastructure_as_code](res/infrastructure_as_code.png)

Infrastructure as Code(IaC) is a method of managing and provisioning IT infrastructure using code, rather than manual configuration.

Benefit:

- Consistency: Same configuration every time, reducing errors.
- Automation: Fast setup and tear-down of environments.
- Scalability: Easily scale infrastructure up or down with code.
- Versioning: Track and roll back changes using Git or other version control.



## Cloud Native

![cloud_native](res/cloud_native.png)

### Cloud Native Anti Patterns

![cloud_native_anti_patterns](res/cloud_native_anti_patterns.png)



## Docker

### Concepts

![docker_concepts](res/docker_concepts.png)

### Workflow

![docker_workflow](res/docker_workflow.png)



## Kubernetes

![what_is_k8s](res/what_is_k8s.png)

### Service Type

![k8s_service_type](res/k8s_service_type.png)

### Tools Ecosystem

![k8s_tools_ecosystem](res/k8s_tools_ecosystem.png)

### Control Plane

![kubernetes_control_plane](res/kubernetes_control_plane.png)

### Kubernetes Pod

![kubernetes_pod](res/kubernetes_pod.png)



## Example 1: Airbnb Runs Distributed Databases on Kubernetes at Scale

![airbnd_distributed_db_k8s](res/airbnd_distributed_db_k8s.png)

### Persistent Volume Claim

![airbnb_k8s_pvc](res/airbnb_k8s_pvc.png)

By combining EBS volumes, PVCs, and a custom operator, Airbnb has found a way to safely run a distributed database on Kubernetes. This allows them to benefit from Kubernetes automation without sacrificing the consistency or availability that a database requires.

### Multi-Cluster Deployment for Fault Tolerance

![airbnb_fault_tolerance](res/airbnb_fault_tolerance.png)

This setup brings several benefits:

- Fault isolation
- Reduced blast radius of deployments
- Canary deployments for safety
- Overprovisioning for resilience



## Summary

### Docker vs K8s

![docker_vs_k8s](res/docker_vs_k8s.jpg)

### DevOps vs NoOps

![dev_ops_vs_no_ops](res/dev_ops_vs_no_ops.png)

### Virtualization vs Containerization

![virtualization_vs_containerization](res/virtualization_vs_containerization.png)



## Reference

[1] [System Design CheatSheet for Interview](https://medium.com/javarevisited/system-design-cheatsheet-4607e716db5a)

[2] [A Crash Course in Kubernetes](https://blog.bytebytego.com/p/a-crash-course-in-kubernetes)

[3] [EP191: Virtualization vs. Containerization](https://blog.bytebytego.com/p/ep191-virtualization-vs-containerization)

[4] [EP178: The Lifecycle of a Kubernetes Pod](https://blog.bytebytego.com/p/ep178-the-lifecycle-of-a-kubernetes)

[5] [Top 8 must-know Docker concepts](https://blog.bytebytego.com/i/145628005/top-8-must-know-docker-concepts)