pipeline {
    agent any
    stages {
        stage('Intro'){

        }
        stage('Test'){
            sshagent (credentials: ['jenkins-server_key']){
                sh 'scp test.txt insights@10.180.1.12:/home/insights/'
            }
        }
    }
}
