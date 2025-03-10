# Software Engineering

---
## CI / CD
- 소프트웨어 개발 및 배포를 자동화 하는 프로세스 &rarr; 새로운 기능을 빠르고 안정적으로 제공

### Continuous Integration (CI, 지속적 통합)
- 여러 개발자가 작성한 코드 변경 사항을 주기적으로 통합하고 자동으로 테스트하여 오류를 빠르게 발견하는 프로세스

#### **CI 주요 단계**
> 1. 개발자가 새로운 코드 변경 사항을 Git등의 **형상 관리 시스템**에 Push
> 2. 자동으로 빌드(Build) 수행
> 3. 유닛 테스트(Unit Test), 통합 테스트(Integration Test) 진행
> 4. 코드 품질 유지를 위해 정적 분석 및 코드 리뷰 도구 사용

**➡️ CI를 통해 코드 변경 사항이 문제없이 빌드 & 테스트되는지 확인**

#### CI 주요 도구 
- Jenkins, Github Actions, GitLab CI/CD, CircleCI, Travis CI

### Continuous Deployment (CD, 지속적 배포)
- CI 이후 배포 단계를 자동화하여 실제 환경에 안정적으로 전달되는 것이 목표
- Continuous Delivery & Continuous Deployment로 나뉨

#### Continuous Delivery 
- CI 과정을 거친 후 운영 환경에 배포할 준비가 된 상태로 자동화 &rarr; 실제 배포는 사람의 승인 후 진행
- Amazon, google 등

#### Continuous Deployment
- CI/CD 파이프라인 끝단까지 **완전 자동화** &rarr; 사람의 개입 없이 배포가 이루어져 신속한 서비스 업데이트 가능
- Netfilx, Facebook, Twitter 등

