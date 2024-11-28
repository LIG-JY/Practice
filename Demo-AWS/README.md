## Description

### EC2Builder

Builder Pattern

```
/**
 * Provides a fluent interface for building Amazon Elastic Compute Cloud (EC2) instances.
 * The {@code EC2Builder} encapsulates the construction logic for EC2 instances and
 * provides a clear API(by fluent builder pattern) for its creation.
 *
 * <p><strong>Example usage:</strong></p>
 * <pre>
 * EC2 instance1 = ec2Builder1
 *                 .setInstanceType(InstanceType.T)
 *                 .setAmi(AMI.UBUNTU)
 *                 .setInstanceId("i-12345678")
 *                 .setSecurityGroups(new ArrayList<>(Arrays.asList(new SecurityGroup(), new SecurityGroup())))
 *                 .setVpcId("vpc-1234")
 *                 .setSubnetId("subnet-1234")
 *                 .setPrivateIp("192.168.1.10")
 *                 .setPublicIp("203.0.113.0")
 *                 .build();
 * </pre>
 */
```

### ELB

Strategy Pattern

```
/**
 * Represents an Elastic Load Balancer (ELB) in the AWS ecosystem.
 * The ELB is responsible for distributing incoming traffic across multiple targets,
 * such as EC2 instances, in one or more Availability Zones.
 * The distribution strategy is determined by the provided {@link ILoadBalancingStrategy}.
 *
 * <p><strong>Example usage:</strong></p>
 * <pre>
 * ELB elb = new ELB(new RoundRobinStrategy(), targetInstances);
 * EC2 targetInstance = elb.getTargetInstance();
 * </pre>
 */
```

### RDSInstance

Multiton Pattern (an extension of Singleton)

```
/**
 * Represents a relational database service (RDS) instance within a specific availability zone (AZ).
 *
 * <p>
 * This class uses a Singleton pattern variant to ensure a limited number of RDS instances
 * are created per availability zone. The maximum number of instances is determined by
 * {@link #MAX_INSTANCES}. Each instance is associated with a specific AZ to ensure
 * high availability and failover capabilities.
 * </p>
 */
```

### RoutingTable

Command Pattern

```
/**
 * Represents a virtual table that maintains the network routes within an Amazon VPC.
 *
 * <p>
 * The {@code RoutingTable} class holds the routes that determine where network traffic is directed.
 * Each VPC has an associated route table, and each subnet in the VPC is explicitly associated with a
 * single route table. The table defines the possible destinations for traffic and the route the traffic
 * should be directed to.
 * </p>
 *
 * <p>
 * For example, when an instance in a VPC sends traffic to a specific IP address, the routing table determines
 * the next hop for that traffic based on the destination IP address.
 * </p>
 */
```

## Test Code

We've set up a class named Client to simulate and test interactions with demo AWS resources. This class is designed to mimic the behavior of a real-world client accessing AWS services. 

```
package aws3tier;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.IntStream;
public class Client {
    private List<EC2> instances = new ArrayList<>(8);
    public static void main(String[] args) {
        Client client = new Client();
        client.builderTest();
        client.elbTest();
        client.rdsTest();
        client.routingTest();
    }
    public void builderTest() {
        EC2Builder ec2Builder1 = new EC2Builder();
        EC2 instance1 = ec2Builder1
                .setInstanceType(InstanceType.T)
                .setAmi(AMI.UBUNTU)
                .setInstanceId("i-12345678")
                .setSecurityGroups(new ArrayList<>(Arrays.asList(new SecurityGroup(), new SecurityGroup())))
                .setVpcId("vpc-1234")
                .setSubnetId("subnet-1234")
                .setPrivateIp("192.168.1.10")
                .setPublicIp("203.0.113.0")
                .build();
        EC2Builder ec2Builder2 = new EC2Builder();
        EC2 instance2 = ec2Builder2
                .setInstanceType(InstanceType.M)
                .setAmi(AMI.MAC_OS)
                .setInstanceId("i-87654321")
                .setSecurityGroups(new ArrayList<>(Arrays.asList(new SecurityGroup(), new SecurityGroup())))
                .setVpcId("vpc-4321")
                .setSubnetId("subnet-4321")
                .setPrivateIp("192.168.1.11")
                .setPublicIp("203.0.113.1")
                .build();
        EC2Builder ec2Builder3 = new EC2Builder();
        EC2 instance3 = ec2Builder3
                .setInstanceType(InstanceType.P)
                .setAmi(AMI.WINDOWS)
                .setInstanceId("i-23456789")
                .setSecurityGroups(new ArrayList<>(Arrays.asList(new SecurityGroup(), new SecurityGroup())))
                .setVpcId("vpc-5678")
                .setSubnetId("subnet-5678")
                .setPrivateIp("192.168.1.12")
                .setPublicIp("203.0.113.2")
                .build();
        EC2Builder ec2Builder4 = new EC2Builder();
        EC2 instance4 = ec2Builder4
                .setInstanceType(InstanceType.HPC)
                .setAmi(AMI.DEBIAN)
                .setInstanceId("i-98765432")
                .setSecurityGroups(new ArrayList<>(Arrays.asList(new SecurityGroup(), new SecurityGroup())))
                .setVpcId("vpc-8765")
                .setSubnetId("subnet-8765")
                .setPrivateIp("192.168.1.13")
                .setPublicIp("203.0.113.3")
                .build();
        this.instances = Arrays.asList(instance1, instance2, instance3, instance4);
        this.instances.forEach(EC2::startInstance);
        IntStream.range(0, this.instances.size())
                .forEach(i -> System.out.println("EC2 Instance " + (i + 1) + " Private IP: " + this.instances.get(i).getPrivateIp()));
    }
    public void elbTest() {
        if (instances.isEmpty()) {
            throw new RuntimeException("No instances have been built yet. Run builderTest() first.");
        }
        List<ILoadBalancingStrategy> strategies = Arrays.asList(
                new RoundRobinStrategy(),
                new LeastConnectionsStrategy(),
                new IPHashStrategy()
        );
        String[] strategyNames = {
                "Round Robin Strategy",
                "Least Connections Strategy",
                "IP Hash Strategy"
        };
        IntStream.range(0, strategies.size())
                .forEach(i -> {
                    ELB elb = new ELB(strategies.get(i), instances);
                    System.out.println("Using " + strategyNames[i] + ": " + elb.getTargetInstance().getPrivateIp());
                });
    }
    public void rdsTest() {
        try {
            RDSInstance instance1 = RDSInstance.getInstance(AvailabilityZone.US_EAST_1A);
            System.out.println("Created RDS instance in AZ: " + instance1.getAz());
            RDSInstance instance2 = RDSInstance.getInstance(AvailabilityZone.US_EAST_1B);
            System.out.println("Created RDS instance in AZ: " + instance2.getAz());
            // 아래 코드는 예외를 발생시킵니다. 이미 US_EAST_1A 에 인스턴스가 있기 때문입니다.
            RDSInstance instance3 = RDSInstance.getInstance(AvailabilityZone.US_EAST_1A);
            System.out.println("Created RDS instance in AZ: " + instance3.getAz());
            // 아래 코드는 예외를 발생시킵니다. 최대 인스턴스 수를 초과하기 때문입니다.
            RDSInstance instance4 = RDSInstance.getInstance(AvailabilityZone.US_EAST_1C);
            System.out.println("Created RDS instance in AZ: " + instance4.getAz());
        } catch (RuntimeException e) {
            System.out.println(e.getMessage());
        }
    }
    public void routingTest() {
        // 커맨드 실행을 위한 인보커 생성
        RouteTableInvoker invoker = new RouteTableInvoker();
        // 라우팅 테이블 및 연결된 VPC 생성
        RoutingTable routingTable = new RoutingTable("rtb-12345678", "vpc-87654321");
        // 로컬, 인터넷 게이트웨이, NAT 게이트웨이 생성
        Local localTarget = new Local("vpc-87654321");
        InternetGateway igw = new InternetGateway("igw-00112233");
        igw.attach("vpc-87654321");
        NatGateway ngw = new NatGateway("ngw-00112233", "vpc-87654321", "subnet-1234");
        // 라우트 생성
        Route localRoute = new Route("10.0.0.0/16", localTarget);
        Route igwRoute = new Route("0.0.0.0/0", igw);
        Route ngwRoute = new Route("10.0.1.0/24", ngw);
        // 라우팅 테이블에 추가하는 command의 모음
        List<ICommand> commandsToAdd = new ArrayList<>();
        commandsToAdd.add(new AddRouteCommand(routingTable, localRoute));
        commandsToAdd.add(new AddRouteCommand(routingTable, igwRoute));
        commandsToAdd.add(new AddRouteCommand(routingTable, ngwRoute));
        // 라우트 추가 명령 실행
        commandsToAdd.stream()
                .forEach(command -> {
                    invoker.setCommand(command);
                    invoker.executeCommand();
                });
        // 특정 라우트(인터넷 게이트웨이) 삭제
        ICommand removeIgwRoute = new RemoveRouteCommand(routingTable, igwRoute);
        invoker.setCommand(removeIgwRoute);
        invoker.executeCommand();
    }
}
```
## 커밋 메시지 규칙

| Tag Name           | Description                                                           |
|--------------------|-----------------------------------------------------------------------|
| `Feat`             | 새로운 기능을 추가                                                        
| `Fix`              | 버그 수정                                                               
| `Design`           | CSS 등 사용자 UI 디자인 변경                                          
| `!BREAKING CHANGE` | 커다란 API 변경의 경우                                               
| `!HOTFIX`          | 급하게 치명적인 버그를 고쳐야하는 경우                                    
| `Style`            | 코드 포맷 변경, 세미 콜론 누락, 코드 수정이 없는 경우                       
| `Refactor`         | 프로덕션 코드 리팩토링                                                
| `Comment`          | 필요한 주석 추가 및 변경                                              
| `Docs`             | 문서 수정                                                             
| `Test`             | 테스트 코드, 리펙토링 테스트 코드 추가, Production Code 변경 없음     
| `Chore`            | 빌드 업무 수정, 패키지 매니저 수정, 패키지 관리자 구성 등 업데이트    
| `Rename`           | 파일 혹은 폴더명을 수정하거나 옮기는 작업만인 경우                    
| `Remove`           | 파일을 삭제하는 작업만 수행한 경우

### Example)
```
git commit -m "Docs: Add commit message guidelines to README"
```
