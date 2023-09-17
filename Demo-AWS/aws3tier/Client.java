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
