pipeline {
    agent any
    stages {
        stage('Intro'){
            steps {
                sh 'echo "Test" >> test.txt'
                sh 'printenv'
            }
        }
        stage('Test'){
            steps {
                sshagent (credentials: ['a3059b33-b6d5-4547-85be-b54f08e0e2fb']){
                    sh 'ssh -v -o StrictHostKeyChecking=no insights@10.180.1.12 uptime'
                    sh 'ssh -v insights@10.180.1.12'
                    sh 'scp test.txt insights@10.180.1.12:/home/insights/'
                }
            }
        }
    }
}
