# -*- coding: utf-8 -*-

import sys
import os
import unittest

current_path = os.path.abspath(os.path.dirname(__file__))
sys.path.append(
    os.path.join(
        current_path,
        "../build"
    )
)

import libsignature


class TestLibSignature(unittest.TestCase):
    """
    Класс для тестирования работы с КриптоПро CSP.
    """
    def setUp(self):
        """
        Задание путей до тестовых файлов
        """
        self._cert_file = os.path.join(current_path, "files/ca.cer")
        self._crl_file = os.path.join(current_path, "files/ca.crl")
        self._user_cert = os.path.join(current_path, "files/user.cer")
        self._sig_file = os.path.join(current_path, "files/test_sign.sig") 
        self._store = "ROOT"

    def test_load_certificate(self):
        """
        Проверка загрузки сертификата.
        """
        result = libsignature.load_certificate(self._cert_file, self._store)
        self.assertIsNone(result)

    def test_load_crl(self):
        """
        Проверка загрузки списка отозванных серитификатов.
        """
        result = libsignature.load_crl(self._crl_file, self._store)
        self.assertIsNone(result)

    def test_verify_cert_chain(self):
        """
        Проверка корректности цепочки сертификатов
        """
        result = libsignature.verify_chain_certificate(self._user_cert)
        self.assertIsNone(result)

    def verify_signature(self):
        """
        Проверка подписи сообщения
        """
        with open(self._sig_file, "rb") as sigfile:
            signature = sigfile.read()
            result = libsignature.vefigy_signature(signature)
            self.assertIsNone(result)


if __name__ == '__main__':
    unittest.main()
